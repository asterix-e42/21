/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grsa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 16:30:08 by tdumouli          #+#    #+#             */
/*   Updated: 2017/10/02 17:12:03 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "mini.h"
#include "lexer.h"
#include <sys/types.h>
#include <sys/wait.h>

int		*fume_pipe(void)
{
	int			*pipe_ret;

	pipe_ret = (int *)malloc(sizeof(int) * 4);
	if (pipe(pipe_ret))
	{
		write(2, "Erreur de création du tube.\n", 20);
		return (NULL);
	}
	*(pipe_ret + 2) = -1;
	*(pipe_ret + 3) = 2;
	return (pipe_ret);
}

void	exec_sparator(t_leaf *branche, int *redir_process_du_futur)
{
	t_token	*tok;
	int		ret_branche;
	int		*redir_process;

	redir_process = NULL;
	tok = ((t_ast *)branche->content)->tok;
	if (((t_ast *)branche->content)->flag == 6 && (redir_process = fume_pipe()))
		create_file(((t_ast *)branche->droite->content)->redir);
	ret_branche = execution(branche->gauche, redir_process, 1);
	if (redir_process)
	{
		close(*(redir_process + 1));
		if (redir_process_du_futur)
		{
			*(redir_process + 1) = *(redir_process_du_futur + 1);
			*(redir_process_du_futur + 3) += *(redir_process + 3) - 1;
		}
		else
			*(redir_process + 2) = 0;
	}
	if (tok->len == 1 || ret_branche == (*tok->start == '|')
			|| ret_branche != (*tok->start == '&'))
		execution(branche->droite, redir_process, 0);
	if (redir_process)
		close_free(&redir_process);
}

int		exec_process(t_ast *ast, int *redir_process, int pipe_g)
{
	int		count;

	if (redir_process && *(redir_process + 2))
		dup2(*(redir_process + 1), atoi(VAR->chop("hidden", "stdout")));
	if (redir_process && !pipe_g)
		dup2(*redir_process, atoi(VAR->chop("hidden", "stdin")));
	if (open_file(ast->redir, ast->argv))
		exit(1);
	if (ast->argv && built_in(ast))
		count = 0;
	else if (ast->argv || (count = 0))
	{
		VAR->add_bout("env", "_", *(ast->argv));
		if (ft_strchr(*(ast->argv), '/'))
			count = new_process(ast, "no such file or directory",
					redir_process);
		else
			count = exe_path(ast->argv, ast, redir_process);
	}
	else
		ft_lstiter(ast->redir, redirpass);
	close_file(ast->redir);
	return (count);
}

int		exec_fourchette(t_ast *ast, int *redir_process, int pipe_g)
{
	int		count;
	pid_t	pid;

	if (!built_in_before_fork(ast))
		return (0);
	pid = fork();
	if (pid == -1)
	{
		erreur(SHELL, "fork", "echec du process");
		return (1);
	}
	if (pid == 0)
		exit(exec_process(ast, redir_process, pipe_g));
	if (pid && !(redir_process && *(redir_process + 2)))
	{
		if (redir_process)
			while ((--*(redir_process + 3)) != -1)
				waitpid(-1, &count, 0);
		waitpid(pid, &count, 0);
	}
	return (WEXITSTATUS(count));
}

int		execution(t_leaf *branche, int *redir_process, int pipe_g)
{
	t_ast	*ast;

	ast = branche->content;
	if (ast->argv)
		VAR->add_bout("env", "_", *ast->argv);
	if (!ast->flag)
		return (exec_fourchette(ast, redir_process, pipe_g));
	else if (ast->flag == 5)
		;
	else if (ast->flag)
		exec_sparator(branche, redir_process);
	return (1);
}
