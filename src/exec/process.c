/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 03:31:16 by tdumouli          #+#    #+#             */
/*   Updated: 2017/10/02 19:53:27 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mini.h"
#include <stdlib.h>

int		new_process(t_ast *ast, char *error, int *flag)
{
	pid_t	pid;
	int		count;

	(void)ast;
	(void)flag;
	if (!access(*(ast->argv), X_OK))
	{
		pid = fork();
		if (pid == -1)
		{
			erreur(SHELL, "fork", "echec du process");
			return (1);
		}
		if (pid == 0)
			execve(*(ast->argv), ast->argv, VAR->chop_all("env"));
		waitpid(-1, &count, WUNTRACED);
		return (WEXITSTATUS(count));
	}
	erreur(SHELL, error, *(ast->argv));
	return (1);
}

/*
** ici a gere assigne mieu
*/

int		exe_path(char **av, t_ast *ast, int *flag)
{
	int		j;
	char	**path;
	char	*tmp;

	if ((j = -1) &&
			(path = ft_strsplit(VAR->chop("env", "PATH"), ':')))
	{
		while (**av && *(path + ++j))
		{
			tmp = ft_strjoini(*(path + j), *av, '/');
			if (!access(tmp, F_OK))
			{
				free(*av);
				*av = tmp;
			}
			else
				free(tmp);
		}
		if (is_dir(*av))
			j = new_process(ast, "command not found", flag);
		freeteuse((void **)path, 1);
	}
	else if ((j = 1))
		new_process(ast, "le PATH est vide", 0);
	return (j);
}
