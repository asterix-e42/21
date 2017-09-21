/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/01 13:26:20 by tdumouli          #+#    #+#             */
/*   Updated: 2017/09/20 23:37:08 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include <stdlib.h>

static t_res_name	lexer_get_separator(char *str)
{
	t_res_name	ret;

	ret.text = str;
	ret.type = TK_REDIR;
	if ((*str == '>' || *str == '<') && (*(str + 1) == '&' ||
				*(str + 1) == *str))
		ret.text += 2;
	else if (*str == '<' || *str == '>')
		++ret.text;
	return (ret);
}

static t_res_name	lexer_get_control(char *str)
{
	t_res_name	ret;

	ret.text = str;
	ret.type = TK_CONTROL;
	if ((*str == *(str + 1)) && (*str == '&' || *str == ';' || *str == '|'))
		ret.text += 2;
	else if (*str == '&' || *str == ';' || *str == '|')
		++ret.text;
	return (ret);
}

static t_res_name	lexer_get_cmd(char *str)
{
	t_res_name	ret;

	ret.text = str;
	ret.type = TK_CMD;
	while (*ret.text && !(ft_isspace(*(ret.text)) || (58 < *(ret.text) &&
				*(ret.text) < 61) || *(ret.text) == '>' || *(ret.text) == 91 ||
				*(ret.text) == 93 || *(ret.text) == '(' || *(ret.text) == ')' ||
				*(ret.text) == '{' || *(ret.text) == '}' ||
				*(ret.text) == '&' || *(ret.text) == '|'))
	{
		++(ret.text);
		if (*ret.text == '=')
			ret.type = TK_ASSEGMT;
	}
	return (ret);
}

static t_res_name	lexer_get_nbr(char *str)
{
	t_res_name	ret;

	ret.text = str;
	if (!ft_isdigit(*str) && (*str != '-' || !ft_isdigit(*(str + 1))))
		return (ret);
	ret.type = TK_NBR;
	if (*str == '-')
		++(ret.text);
	while (ft_isdigit(*(ret.text)))
		++(ret.text);
	if (!(!*ret.text || ft_isspace(*(ret.text)) || (58 < *(ret.text) &&
				*(ret.text) < 61) || *(ret.text) == '>' || *(ret.text) == '|'))
		ret.text = str;
	return (ret);
}

static t_res_name	lexer_get_space(char *str)
{
	t_res_name	ret;

	ret.text = str;
	if (*str != ' ')
		return (ret);
	ret.type = TK_BLANK;
	while (ft_isspace(*ret.text))
		++(ret.text);
	return (ret);
}

static t_res_name	lexer_get_newline(char *str)
{
	t_res_name	ret;

	ret.text = str;
	if (*str != '\n')
		return (ret);
	ret.type = TK_NEWLINE;
	while (*(ret.text) == '\n')
		++(ret.text);
	return (ret);
}

static t_res_name	lexer_get_cote(char *str)
{
	t_res_name	ret;

	ret.text = str;
	if (*ret.text == '\'' || *ret.text == '"')
	{
		if (*ret.text == '\'')
			ret.type = TK_SCOTE;
		else
			ret.type = TK_DCOTE;
		while ((ret.text = ft_strchr(ret.text + 1, *ret.text)))
			if ((ret.type == TK_SCOTE || *(ret.text - 1) != '\\') && ++ret.text)
				break ;
	}
	return (ret);
}

static t_res_name	lexer_get_comment(char *str)
{
	t_res_name	ret;

	ret.text = str;
	if (!((*str == '#' && 1) || (*str == '\n' && *(str + 1) == '#')))
		return (ret);
	ret.type = TK_COMMENT;
	ret.text = ft_strchr(str + 1, '\n') + 1;
	return (ret);
}

static t_res_name	lexer_get_reserv(char *str)
{
	t_list		*res;
	t_res_name	ret;
	int			tmp;

	res = get_resv();
	ret.text = str;
	while (res)
	{
		tmp = ft_strlen(((t_res_name *)res->content)->text);
		if (!ft_strncmp(((t_res_name *)res->content)->text, str, tmp)
				&& ft_isspace(*(str + tmp)))
		{
			ft_putstr(((t_res_name *)res->content)->text);
			ret.text = str + ft_strlen(((t_res_name *)res->content)->text);
			ret.type = ((t_res_name *)res->content)->type;
			return (ret);
		}
		res = res->next;
	}
	return (ret);
}

static t_res_name	lexer_get_cont(char *str)
{
	t_res_name	ret;
	t_res_name	parc;

	ret.text = str;
	if (*ret.text == ']' || *ret.text == '}' || *ret.text == ')')
		ret.text = NULL;
	if (!ret.text || (*ret.text != '[' && *ret.text != '{' && *ret.text != '('))
		return (ret);
	if (*ret.text == '(')
		ret.type = TK_PARENT;
	else if (*ret.text == '{')
		ret.type = TK_ACOLAD;
	else
		ret.type = TK_CROCHET;
	while ((++ret.text) && *ret.text && *ret.text != *str + 2 - (*str == '(') &&
			(parc.text = ret.text))
		if (verrif_all(ret.text, &parc))
			ret.text = parc.text - 1;
	if (!ret.text || !*ret.text)
		ret.text = NULL;
	else
		++ret.text;
	return (ret);
}

int					verrif_all(char *str, t_res_name *parc)
{
	return (str && ((*parc = lexer_get_comment(parc->text)).text != str
				|| (*parc = lexer_get_control(parc->text)).text != str
				|| (*parc = lexer_get_reserv(parc->text)).text != str
				|| (*parc = lexer_get_separator(parc->text)).text != str
				|| (*parc = lexer_get_space(parc->text)).text != str
				|| (*parc = lexer_get_nbr(parc->text)).text != str
				|| (*parc = lexer_get_newline(parc->text)).text != str
				|| (*parc = lexer_get_cote(parc->text)).text != str
				|| (*parc = lexer_get_cont(parc->text)).text != str
		|| (parc->text && (*parc = lexer_get_cmd(parc->text)).text != str)));
}

void				rm_token(void *tok, size_t rien)
{
	(void)rien;
	free(((t_token *)tok)->start);
}

t_list				*new_token(char *str)
{
	t_token		ret;

	ret.start = str;
	ret.len = 0;
	ret.type = TK_END;
	return (ft_lstnew(&ret, sizeof(t_token)));
}

void				set_token_len(t_list *toks, t_res_name token)
{
	t_token		*tok;

	tok = toks->content;
	if (!toks)
		return ;
	if (token.text)
		tok->len = token.text - (tok)->start;
	else
		tok->len = ft_strlen(tok->start);
	tok->type = token.type;
}

t_lexer				*lexer_init(char *str)
{
	t_lexer		*ret;
	char		*tmp;

	ret = (t_lexer *)malloc(sizeof(t_lexer));
	tmp = ft_strdup(str);
	ret->input = tmp;
	ret->token = NULL;
	return (ret);
}

void				lexer(t_lexer *tex)
{
	t_res_name	parc;
	char		*str;
	t_list		*toks;

	ft_lstaddend(&(tex->token), new_token(parc.text = tex->input));
	toks = tex->token;
	while ((str = parc.text) && *str)
	{
		while (verrif_all(str, &parc) && parc.text)
		{
			set_token_len((toks), parc);
			ft_lstaddend(&(toks), new_token(parc.text));
			toks = toks->next;
			str = parc.text;
		}
		if (!parc.text || !*parc.text)
			return ;
	}
	set_token_len((toks), parc);
}
