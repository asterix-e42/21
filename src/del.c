/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 00:39:32 by tdumouli          #+#    #+#             */
/*   Updated: 2017/09/28 00:44:03 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mini.h"
#include <stdlib.h>

void	del_t_token(void *tok, size_t tamere)
{
	(void)tamere;
	free(tok);
}

void	del_t_redir(void *redir, size_t tamere)
{
	(void)tamere;
	freeteuse((void **)((t_redir *)redir)->file, 0);
	free(redir);
}

void	del_t_ast(void *ast, size_t tamere)
{
	(void)tamere;
	freeteuse((void **)((t_ast *)ast)->assign, 1);
	freeteuse((void **)((t_ast *)ast)->argv, 1);
	ft_lstdel(&(((t_ast *)ast)->redir), del_t_redir);
	free(ast);
}
