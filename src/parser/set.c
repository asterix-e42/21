/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 01:59:19 by tdumouli          #+#    #+#             */
/*   Updated: 2017/10/02 18:02:17 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdlib.h>

/*
** env non gere
*/

void		set_ast_assignement(t_token *elem, t_ast *ast)
{
	char		**tmp;
	char		*str;
	int			lenght;

	lenght = -1;
	if (!ast->assign)
		++lenght;
	else
		while (*(ast->assign + ++lenght))
			;
	str = ft_strnew(elem->len);
	ft_strncat(str, elem->start, elem->len);
	tmp = str_str_ralloc(1, ast->assign);
	*(tmp + lenght) = str;
	free(ast->assign);
	ast->assign = tmp;
}

void		set_ast_args(t_token *elem, t_ast *ast)
{
	char		**tmp;
	char		**tmp2;
	char		*str;
	int			flag_cote;

	flag_cote = (elem->type == TK_SCOTE || elem->type == TK_DCOTE);
	str = ft_strnew(elem->len - (2 * flag_cote));
	ft_strncat(str, elem->start + flag_cote, elem->len - (2 * flag_cote));
	if (elem->type != TK_SCOTE)
		change(&str, flag_cote, ast->argv);
	if (flag_cote)
		tmp2 = str_strdup(str);
	else
		tmp2 = ft_strsplit(str, ' ');
	if ((flag_cote = str_strlen((void **)tmp2)))
	{
		tmp = str_str_ralloc(flag_cote, ast->argv);
		while (flag_cote--)
			*(tmp + ast->argc + flag_cote) = *(tmp2 + flag_cote);
		free(ast->argv);
		free(tmp2);
		ast->argv = tmp;
		ast->argc = str_strlen((void **)ast->argv);
	}
	free(str);
}
