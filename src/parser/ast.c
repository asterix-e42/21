/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 16:09:23 by tdumouli          #+#    #+#             */
/*   Updated: 2017/10/04 22:26:27 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "mini.h"
#include <unistd.h>
#include <stdlib.h>

int			foret(t_leaf **start, t_leaf **pourquoi, t_token *tok, t_leaf *tmp)
{
	if (tok->len == 1 && *tok->start == ';')
		((t_ast *)(tmp)->content)->flag = 9;
	else if (((t_ast *)(*pourquoi)->content)->tok->type == TK_CONTROL)
	{
		((t_ast *)((*start)->content))->flag = 255;
		write(2, "porse error\n", 12);
		ft_treeaddd(*pourquoi, tmp);
		return (1);
	}
	else if (tok->len == 1 && *tok->start == '&')
		((t_ast *)(tmp)->content)->flag = 9;
	else if (tok->len == 2 && (*tok->start == '&' || *tok->start == '|'))
	{
		while ((*pourquoi)->prev && ((t_ast *)(*pourquoi)->content)->flag < 9)
			*pourquoi = (*pourquoi)->prev;
		((t_ast *)(tmp)->content)->flag = 8;
	}
	else if (tok->len == 1 && *tok->start == '|')
	{
		while ((*pourquoi)->prev && ((t_ast *)(*pourquoi)->content)->flag < 8)
			*pourquoi = (*pourquoi)->prev;
		((t_ast *)(tmp)->content)->flag = 6;
	}
	return (0);
}

int			add_control(t_leaf **start, t_leaf **pourquoi, t_token *tok)
{
	t_leaf		*tmp;

	if (!(tmp = new_ast((t_lexer *)tok, 0)))
		return (1);
	if (foret(start, pourquoi, tok, tmp))
		return (1);
	if ((!(*pourquoi)->prev && ((t_ast *)(tmp)->content)->flag >=
	((t_ast *)(*start)->content)->flag) || ((t_ast *)(tmp)->content)->flag == 9)
	{
		tmp->gauche = *start;
		*start = tmp;
	}
	else
		ft_treeaddd(*pourquoi, tmp);
	*pourquoi = tmp;
	return (0);
}

void		affectation(t_lexer *lex, t_leaf *milieu)
{
	if (((((t_token *)(*lex).token->content)->type) == TK_NBR &&
				(((t_token *)(*lex).token->next->content)->type) == TK_REDIR) ||
			(((t_token *)(*lex).token->content)->type) == TK_REDIR)
		ft_lstadd(&(((t_ast *)milieu->content)->redir), new_redir(lex));
	else if ((((t_token *)(*lex).token->content)->type) == TK_ASSEGMT)
		set_ast_assignement((*lex).token->content, milieu->content);
	else if ((((t_token *)(*lex).token->content)->type) == TK_CMD ||
			(((t_token *)(*lex).token->content)->type) == TK_NBR ||
			(((t_token *)(*lex).token->content)->type) == TK_SCOTE ||
			(((t_token *)(*lex).token->content)->type) == TK_DCOTE)
		set_ast_args((*lex).token->content, milieu->content);
}

/*
**		a faire ast
**
**		else if ((((t_token *)lex.token->content)->type) == TK_ACOLAD)
**			;
**		else if ((((t_token *)lex.token->content)->type) == TK_PARENT)
**			;
*/

t_leaf		*ast(t_lexer lex)
{
	t_leaf		*start;
	t_leaf		*parceque;

	if (!(start = new_ast(&lex, 1)))
		return (NULL);
	parceque = start;
	while (((t_token *)lex.token->content)->len)
	{
		if ((((t_token *)lex.token->content)->type) == TK_CONTROL)
		{
			if (add_control(&start, &parceque, lex.token->content))
				return (start);
			lex.token = lex.token->next;
			if (ft_treeaddd(parceque, new_ast(&lex, 1)))
				return (start);
			parceque = parceque->droite;
		}
		affectation(&lex, parceque);
		if (((t_token *)lex.token->content)->len)
			lex.token = lex.token->next;
	}
	return (start);
}
