/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fenster.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 00:09:48 by tdumouli          #+#    #+#             */
/*   Updated: 2017/09/02 21:00:41 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <lexer.h>

int		main(int ac, char **av, char **ae)
{
	VAR->init("env");
	VAR->init("hist");
	VAR->add_bout("hist", "comp", "1");
	VAR->add_bout("hist", "rang", "1");
	VAR->init("alias");
	VAR->add_bout("alias", "l", "ls -la");
	VAR->add("env", ae, -1);
	(void)ac;
	sheel(av);
	ft_mini_exit((void *)0);
}

void	del_t_token(void *tok, size_t tamere)
{
	(void)tamere;
	free(tok);
}

void	del_t_redir(void *redir, size_t tamere)
{
	(void)tamere;
	if (((t_redir *)redir)->fd)
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

void	sheel(char **av)
{
	char		*string;
	t_lexer		*tex;
	t_leaf		*start;

	whereareyou("PWD");
	VAR->add_bout("env", "_", *av);
	lvlup();
	while (1)
	{
		write(1, "🦄 > \x1b[39m", 12);
		if (!(string = saisie()))
			continue ;
		tex = lexer_init(string);
		lexer(tex);
		start = ast(*tex);
		if (start)
			execution(start, NULL);
		ft_treedel(&start, del_t_ast);
		free(start);
		free(tex->input);
		ft_lstdel(&(tex->token), del_t_token);
		free(tex);
		free(string);
	}
}
