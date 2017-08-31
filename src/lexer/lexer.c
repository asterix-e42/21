
#include "lexer.h"
#include "libft.h"
#include <stdlib.h>

#include <unistd.h>

void	set_token_len(t_list *tok, t_res_name re);
t_list	*new_token(char *str);
void	rm_token(void *tok, size_t rien);
int		verrif_all(char *str, t_res_name *parc);
static t_res_name		lexer_get_separator(char *str)
{
	t_res_name	ret;

	ret.text = str;
	ret.type = TK_REDIR;
	//if (*str == '<' && *(str + 1) == '<' && *(str + 2) == '-')
	//	ret.text += 3;
	//if (*str == '>' && *(str + 1) == '|')
	//	ret.text += 2;
	if ((*str == '>' || *str == '<') && (*(str + 1) == '&' ||
				*(str + 1) == *str))
		ret.text += 2;
	else if (*str == '<' || *str == '>')
		++ret.text;
	return (ret);
}

static t_res_name		lexer_get_control(char *str)
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

static t_res_name		lexer_get_cmd(char *str)
{
	t_res_name	ret;

	ret.text = str;
	//if (!ft_isalpha(*str) || *str == '/')
	//	return (ret);
	ret.type = TK_CMD;
	//while (*ret.text && (ft_isalpha(*ret.text) || *ret.text == '/'))
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

static t_res_name		lexer_get_nbr(char *str)
{
	t_res_name	ret;

	ret.text = str;
	if (!ft_isdigit(*str) && (*str != '-' || !ft_isdigit(*(str + 1))))
		return (ret);
	//write(1, "ff", 2);
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

static t_res_name		lexer_get_space(char *str)
{
	t_res_name ret;

	ret.text = str;
	if (*str != ' ')
		return (ret);
	ret.type = TK_BLANK;
	while (ft_isspace(*ret.text))
		++(ret.text);
	return (ret);
}

static t_res_name		lexer_get_newline(char *str)
{
	t_res_name ret;

	ret.text = str;
	if (*str != '\n')
		return (ret);
	ret.type = TK_NEWLINE;
	while (*(ret.text) == '\n')
		++(ret.text);
	return (ret);
}

static t_res_name		lexer_get_cote(char *str)
{
	t_res_name ret;

	ret.text = str;
	if (*ret.text == '\'' || *ret.text == '"')
	{
		//write(1, "h", 1);
		if (*ret.text == '\'')
			ret.type = TK_SCOTE;
		else
			ret.type = TK_DCOTE;
		if (!ft_strchr(ret.text + 1, *ret.text))
			ret.text = NULL; // a remplir
		else
			ret.text = ft_strchr(ret.text + 1, *ret.text) + 1;
	}
	return (ret);
}

static t_res_name		lexer_get_comment(char *str)
{
	t_res_name ret;

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
		if (!ft_strncmp(((t_res_name *)res->content)->text, str, tmp) && ft_isspace(*(str + tmp)))
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

static t_res_name		lexer_get_cont(char *str)
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
		if(verrif_all(ret.text, &parc))
			ret.text = parc.text - 1;
	if (!ret.text || !*ret.text)
		ret.text = NULL;
	else
		++ret.text;
	return (ret);
}

int		verrif_all(char *str, t_res_name *parc)
{
	//write(1, "r", 1);
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

void	rm_token(void *tok, size_t rien)
{
	(void) rien;
	free(((t_token *)tok)->start);
}

t_list	*new_token(char *str)
{
	t_token		ret;

	ret.start = str;
	ret.len = 0;
	ret.type = TK_END;
	return (ft_lstnew(&ret, sizeof(t_token)));
}

void	set_token_len(t_list *toks, t_res_name token)
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

t_lexer		*lexer_init(char *str)
{
	t_lexer		*ret;
	char		*tmp;

	ret = (t_lexer *)malloc(sizeof(t_lexer));
	tmp = ft_strdup(str);
	//ret->input = NULL;
	//if (*tmp)
	ret->input = tmp;
	//else
	//	free(tmp);
	ret->token = NULL;
	return (ret);
}

void	lexer(t_lexer *tex)
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
		else
		{
			++parc.text;
			parc.type = TK_PLUSTARD;
			set_token_len((toks), parc);
			ft_lstaddend(&(toks), new_token(parc.text));
			toks = toks->next;
		}
	}
	set_token_len((toks), parc);
}

void	print_lex(t_lexer tex)
{
	while (((t_token *)tex.token->content) &&
			((t_token *)tex.token->content)->len)
	{
		if ((((t_token *)tex.token->content)->type) == TK_COMMENT)
			ft_putendl("#");
		else
		{
			ft_putnbr(((t_token *)tex.token->content)->len);
			ft_putstr("->");
			ft_putchar('[');
			if ((((t_token *)tex.token->content)->type) == TK_CMD)
				ft_putchar('C');
			if ((((t_token *)tex.token->content)->type) == TK_DCOTE)
				ft_putchar('"');
			if ((((t_token *)tex.token->content)->type) == TK_BLANK)
				ft_putchar(' ');
			if ((((t_token *)tex.token->content)->type) == TK_CONTROL)
				ft_putchar('S');
			if ((((t_token *)tex.token->content)->type) == TK_WHILE)
				ft_putchar('W');
			if ((((t_token *)tex.token->content)->type) == TK_NBR)
				ft_putchar('N');
			if ((((t_token *)tex.token->content)->type) == TK_PLUSTARD)
				ft_putchar('M');
			if ((((t_token *)tex.token->content)->type) == TK_NEWLINE)
				ft_putchar('L');
			ft_putchar(']');
			ft_putchar('[');
			ft_putchar(*((t_token *)tex.token->content)->start);
			ft_putchar(']');
			write(1, ((t_token *)tex.token->content)->start,
					((t_token *)tex.token->content)->len);
			ft_putchar('\n');
		}
		tex.token = tex.token->next;
	}
}
/*
int		main(int ac, char **av)
{
	char		*s;
	t_lexer		*tex;

	if (ac != 1)
	{
		s = *(av + 1);
		tex = lexer_init(s);
		lexer(tex);
		if (tex)
		{
			print_lex(*tex);
			ast(*tex);
		}
	}
	else
		write(1, "no comment\n", 11);
	//	while(1);
}*/
