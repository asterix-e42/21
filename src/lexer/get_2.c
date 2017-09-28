/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 02:39:06 by tdumouli          #+#    #+#             */
/*   Updated: 2017/09/28 02:57:32 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_res_name	lexer_get_space(char *str)
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

t_res_name	lexer_get_newline(char *str)
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

t_res_name	lexer_get_comment(char *str)
{
	t_res_name	ret;

	ret.text = str;
	if (!((*str == '#' && 1) || (*str == '\n' && *(str + 1) == '#')))
		return (ret);
	ret.type = TK_COMMENT;
	if ((int)(ret.text = ft_strchr(str + 1, '\n') + 1) == 1)
		ret.text = ft_strchr(str + 1, '\0');
	return (ret);
}

t_res_name	lexer_get_reserv(char *str)
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
