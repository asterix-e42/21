/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 02:39:06 by tdumouli          #+#    #+#             */
/*   Updated: 2017/10/02 16:30:20 by tdumouli         ###   ########.fr       */
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

t_res_name	lexer_get_control(char *str)
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

t_res_name	lexer_get_comment(char *str)
{
	t_res_name	ret;

	ret.text = str;
	if (!((*str == '#' && 1) || (*str == '\n' && *(str + 1) == '#')))
		return (ret);
	ret.type = TK_COMMENT;
	if (!(ret.text = ft_strchr(str + 1, '\n')))
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
