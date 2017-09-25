/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fenster.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 00:09:48 by tdumouli          #+#    #+#             */
/*   Updated: 2017/09/25 19:41:02 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <lexer.h>
#include <signal.h>

int		main(int ac, char **av, char **ae)
{
	VAR->init("env");
	VAR->init("hist");
	VAR->init("hidden");
	VAR->add_bout("hidden", "comp", "1");
	VAR->add_bout("hidden", "rang", "1");
	VAR->add_bout("hidden", "stdin", "0");
	VAR->add_bout("hidden", "stdout", "1");
	VAR->add_bout("hidden", "stderr", "2");
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

void	execmain(char *string)
{
	t_lexer		*tex;
	t_leaf		*start;

	tex = lexer_init(string);
	lexer(tex);
	start = ast(*tex);
	if (!VAR->chop("hidden", "parse"))
		execution(start, NULL, 0);
	else
		VAR->unset("hidden", "parse");
	ft_treedel(&start, del_t_ast);
	free(start);
	free(tex->input);
	ft_lstdel(&(tex->token), del_t_token);
	free(tex);
	free(string);
}

void	sig_fpe(int sig)
{
	(void)sig;
	write(1, "\n", 1);
}

int		coteacote(char *string)
{
	char *tmp;

	if ((tmp = ft_strchr(string, '\''))
	|| (tmp = ft_strchr(string, '\"')))
	{
		while ((tmp = ft_strchr(tmp + 1, *tmp)))
			if ((*tmp == '\'' || *(tmp - 1) != '\\') && ++tmp)
				return (coteacote(tmp));
	}
	else
		return (0);
	return (1);
}

void	sheel(char **av)
{
	char		*string;
	char		*tmp;

	whereareyou("PWD");
	VAR->add_bout("env", "_", *av);
	lvlup("env", "SHLVL");
	if (signal(SIGINT, sig_fpe) == SIG_ERR)
		write(2, "Le gestionnaire de signal n'a pu etre defini.", 45);
	while (1)
	{
		while (!(string = saisie("🦄 ", 1)))
			set_hist(string);
		while (coteacote(string))
		{
			ft_stralloc(&string, "\n");
			if (!(tmp = saisie("quote", 0)))
				*string = '\0';
			else
				ft_stralloc(&string, tmp);
			free(tmp);
		}
		set_hist(string);
		execmain(string);
	}
}
