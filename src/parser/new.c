/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 02:00:05 by tdumouli          #+#    #+#             */
/*   Updated: 2017/10/04 22:26:34 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdlib.h>

int			next_type(t_list *lex, t_token_type type)
{
	t_token		*tok;

	while ((tok = (t_token *)lex->next->content) && tok->len && (
				tok->type == TK_BLANK))
		lex = lex->next;
	return (tok->type == type || !tok->len);
}

t_list		*new_redir(t_lexer *lex)
{
	t_redir		ret;

	ret.fd = 0;
	ret.file = (void *)0;
	if ((((t_token *)lex->token->content)->type) == TK_NBR)
	{
		ret.in = ft_atoi(((t_token *)lex->token->content)->start);
		lex->token = lex->token->next;
	}
	else
		ret.in = ('>' == *((t_token *)lex->token->content)->start);
	ret.tok = ((t_token *)lex->token->content);
	lex->token = lex->token->next;
	ret.out = (*(((t_token *)lex->token->content)->start - 1) == '&') ? -1 : -2;
	while (((t_token *)lex->token->content)->type == TK_BLANK)
		lex->token = lex->token->next;
	if (ret.out == -1 && ((t_token *)lex->token->content)->type == TK_NBR)
		ret.out = ft_atoi(((t_token *)lex->token->content)->start);
	else
		ret.file = ft_strndup((((t_token *)lex->token->content)->start),
				(((t_token *)lex->token->content)->len));
	return (ft_lstnew(&ret, sizeof(t_redir)));
}

t_leaf		*new_ast(t_lexer *lx, char fg)
{
	t_ast		ret;
	t_leaf		*leaf;
	t_token		*tk;

	while ((tk = lx->token->content) && fg && (tk->len) && tk->type == TK_BLANK)
		lx->token = lx->token->next;
	ret = (t_ast) {NULL, 0, 0, 0, 0, (fg) ? tk : (t_token *)lx};
	if (fg && (tk->type == TK_CONTROL || !tk->len))
		return (parse_error(tk, lx));
	else if (fg && tk->type == TK_ACOLAD)
	{
		if (!next_type(lx->token, TK_CONTROL))
			return (NULL);
		else
		{
			leaf = ft_treenew(&ret, sizeof(t_ast));
			leaf->droite = new_secleaf(tk);
			((t_ast *)(leaf)->content)->flag = 5;
		}
	}
	else
		leaf = ft_treenew(&ret, sizeof(t_ast));
	return (leaf);
}

t_leaf		*new_secleaf(t_token *tok)
{
	t_lexer		*sec_lex;
	char		*tmp;

	if (tok->len <= 2)
		return (NULL);
	tmp = ft_strsub(tok->start, 1, tok->len - 2);
	sec_lex = lexer_init(tmp);
	free(tmp);
	lexer(sec_lex);
	if (sec_lex)
		return (ast(*sec_lex));
	return (NULL);
}
