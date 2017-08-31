/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fenster.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 00:09:48 by tdumouli          #+#    #+#             */
/*   Updated: 2017/08/31 04:05:25 by tdumouli         ###   ########.fr       */
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
	VAR->init("alias");
	VAR->add_bout("alias", "l", "ls -la");
	VAR->add("env", ae, -1);
	(void)ac;
	sheel(av);
	ft_mini_exit((void *)0);
}

void del_t_token(void *tok, size_t tamere)
{
	(void)tamere;
	//(void)tok;
	free(((t_token *)tok)->start);
}

void del_t_redir(void *redir, size_t tamere)
{
	(void)tamere;
	//(void)tok;
	free(((t_redir *)redir)->file);
}

void del_t_ast(void *ast, size_t tamere)
{
	(void)tamere;
	freeteuse((void **)((t_ast *)ast)->assign, 1);
	freeteuse((void **)((t_ast *)ast)->cmd, 0);
	freeteuse((void **)((t_ast *)ast)->argv, 1);
	ft_lstdel(&(((t_ast *)ast)->redir), del_t_redir);
	//freeteuse((void **)((t_ast *)ast)->tok->start, 0);
}

void	sheel(char **av)
{
	char	*string;
	//char	*tmp;
	t_lexer     *tex;
	t_leaf		*start;

	//VAR->print("env", NULL);
	whereareyou("PWD");
	VAR->add_bout("env", "_", *av);
	//env_add("_", *av);
	lvlup();
	while (1)
	{
		write(1, "🦄 > \x1b[39m", 12);
		string = saisie();
		tex = lexer_init(string);
		lexer(tex);
		if (tex)
		{
		//	print_lex(*tex);
			start = ast(*tex);
			write(1, "\n", 1);
			if (start)
				execution(start, NULL);
		free(tex->input);
		ft_treedel(&start, del_t_ast);
		}
		free(string);
	}
}
