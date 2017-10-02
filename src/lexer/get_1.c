/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 02:37:44 by tdumouli          #+#    #+#             */
/*   Updated: 2017/10/02 17:09:21 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_res_name	lexer_get_separator(char *str)
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

t_res_name	lexer_get_cote(char *str)
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

t_res_name	lexer_get_cmd(char *str)
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
		{
			if (*(ret.text + 1) == '"' || *(ret.text + 1) == '\'')
				ret = lexer_get_cote(ret.text + 1);
			ret.type = TK_ASSEGMT;
		}
	}
	return (ret);
}

t_res_name	lexer_get_nbr(char *str)
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

t_res_name	lexer_get_cont(char *str)
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
