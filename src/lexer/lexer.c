/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/01 13:26:20 by tdumouli          #+#    #+#             */
/*   Updated: 2017/10/02 16:26:52 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "g.h"
#include "libft.h"
#include <stdlib.h>

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
	int			ite;

	ft_lstaddend(&(tex->token), new_token(parc.text = tex->input));
	toks = tex->token;
	ite = 1000;
	while ((str = parc.text) && *str && ite)
	{
		while (verrif_all(str, &parc) && parc.text)
		{
			set_token_len((toks), parc);
			ft_lstaddend(&(toks), new_token(parc.text));
			toks = toks->next;
			str = parc.text;
			ite = 1000;
		}
		if (!parc.text || !*parc.text)
			return ;
		--ite;
	}
	if (!ite)
		erreur(SHELL, "lexer iteration", str);
	set_token_len((toks), parc);
}
