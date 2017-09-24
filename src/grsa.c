/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grsa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 16:30:08 by tdumouli          #+#    #+#             */
/*   Updated: 2017/09/24 02:00:11 by tdumouli         ###   ########.fr       */
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


void	change(char **s, int flagcote, char **test)
{
	int		i;
	char	*vr;

	i = 0;
	while (*(*s + i))
	{
		if (*(*s + i) == '$' && *(*s + i + 1))
			i += variable(s, i) - 1;
		else if (!flagcote && i == 0 && (vr = VAR->chop("alias", *s)) && !test)
			i = copy(s, 0, vr, ft_strlen(*s)) - 1;
		else if (*(*s + i) == '\\')
			i += echapement(s, i);
		else if (*(*s + i) == '*')
			i += 0;
		++i;
	}
}

int		fd_is_valid(int fd, int has_mode)
{
	int		fd_flags;
	int		fd_modes;

	fd_modes = fcntl(fd, F_GETFL);
	fd_flags = fcntl(fd, F_GETFD);
	return (fd_flags != -1 && (has_mode == -1 || fd_modes & has_mode));
}

int		agregation(t_redir *redi)
{
	if (redi->out <= -1)
	{
		if (ft_strcmp(redi->file, "-") == 0)
		{
			close(redi->in);
			return (0);
		}
		erreur(SHELL, redi->file, "can only be digits{eoc}");
		return (1);
	}
	if (redi->out > 9)
		return (1);
	if(dup2(redi->out, redi->in) == -1)
	{
		erreur(SHELL, ft_itoa(redi->out), "bad file descriptor");
		return (1);
	}
	return (0);
}

void	close_file(t_list *redir_start)
{
	t_redir	*redi;
	while (redir_start && (redi = ((t_redir *)redir_start->content)))
	{
		if (redi->fd <= -1)
			close(redi->fd);
		redir_start = redir_start->next;
	}
}

int		open_file(t_list *redir_start, void *flag_av)
{
	int		open_fg;
	t_redir	*redi;

	while (redir_start && (redi = ((t_redir *)redir_start->content)))
	{
		if (*redi->tok->start == '<')
		{
			if (*(redi->tok->start + 1) == '<')
				d_redir_g(redi, flag_av);
			else if (*(redi->tok->start + 1) == '&')
			{
				if (agregation(redi))
					return (1);
			}
			else
			{
					redi->out = redi->in;
					if ((redi->fd = open(redi->file, O_RDONLY | O_NOCTTY)) < 0)
					{
						erreur(SHELL, "open", "can't open");
						return (1);
					}
					redi->in = redi->fd;
			}
		}
		else if (*redi->tok->start == '>')
		{
			if (*(redi->tok->start + 1) == '&')
			{
				if (agregation(redi))
					return (1);
			}
			else
			{
			open_fg = (*(redi->tok->start + 1) != '>') ? O_TRUNC : O_APPEND;
			if (!((redi->fd = open(redi->file,
	O_CREAT | O_WRONLY | open_fg, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) > 0))
				return (1);
			redi->out = redi->fd;
			}
		}
		//ft_putnbr(redi->in);
		//ft_putnbr(redi->out);
		if (flag_av)
		{
			//	write(1, "1 ", 1);
			dup2(redi->out, redi->in);
		}

		/*
		   ft_putnbr(redi->in);
		   ft_putnbr(isatty(redi->in));
		   ft_putnbr(isatty(redi->out));
		   if (isatty(redi->in) && isatty(redi->out))
		   dup2(redi->out, redi->in);
		   else
		   write(1, "pas ouvert\n", 10);*/
		redir_start = redir_start->next;
	}
	return (0);
}

void	create_file(t_list *redir_start)
{
	//int		open_close;
	t_redir	*redir;

	while (redir_start && (redir = ((t_redir *)redir_start->content)))
	{
		if (redir->out <= -1 && *redir->tok->start == '>')
			creat(redir->file,
								S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		redir_start = redir_start->next;
	}
}

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
		waitpid(-1, &count, 0);
		return (WEXITSTATUS(count));
	}
	erreur(SHELL, error, *(ast->argv));
	return (1);
}
/*
 ** ici a gere assigne mieu
 */
int		built_in_before_fork(t_ast *ast)
{
	char	**av;
	int		ret;

	if (!(av = ast->argv) || !*av)
		return (1);
	ret = 0;
	if (ast->argv && !ft_strcmp(*(ast->argv), "exit"))
		ft_mini_exit(ast->argv);
	if (VAR->chop(*av, 0))
		VAR->print(*av, NULL);
	else if (!ft_strcmp(*av, "cd"))
		built_cd(av);
	else if (!ft_strncmp(*av, "set", 3))
		ft_setenv(ast);
	else if (!ft_strncmp(*av, "unset", 5) && ft_strncmp(*av + 5, "hidden", 6))
		while (*(++av))
			VAR->unset(*ast->argv + 5, *av);
	else
		ret = 1;
	return (ret);
}

int		built_in(t_ast *ast)
{
	char	**av;

	if (!(av = ast->argv) || !*av)
		return (1);
	else if (!ft_strcmp(*av, "echo"))
		ft_echo(av);
	else
		return (0);
	return (1);
}

int		exe_path(char **av, t_ast *ast, int *flag)
{
	int		j;
	char	**path;
	char	*tmp;

	j = 1;
	if ((path = ft_strsplit(VAR->chop("env", "PATH"), ':')))
	{
		j = -1;
		while (*(path + ++j))
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
	else
		new_process(ast, "le PATH est vide", 0);
	return (j);
}

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
	if (tok->len == 1 && *tok->start == '|')
		if ((redir_process = fume_pipe()))
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
	if (tok->len == 1 || ret_branche == (*tok->start == '|') ||
			ret_branche != (*tok->start == '&'))
		execution(branche->droite, redir_process, 0);
/*	if (tok->len == 1 && *tok->start == '|')
		waitpid(-1, &ret_branche, 0);
*/	if (redir_process)
	{
		close(*redir_process);
		free(redir_process);
	}
}

void	return_back_fd(char *test)
{
	int		tmp;

	tmp = ft_atoi(test);
	dup(tmp);
	close(tmp);
}

void	return_back(void)
{
	char	*test;

	test = VAR->chop("hidden", "stdin");
	if (ft_strcmp(test, "0"))
	{
		close(0);
		return_back_fd(test);
		VAR->add_bout("hidden", "stdin", "0");
	}
	test = VAR->chop("hidden", "stdout");
	if (ft_strcmp(test, "1"))
	{
		close(1);
		return_back_fd(test);
		VAR->add_bout("hidden", "stdin", "1");
	}
	test = VAR->chop("hidden", "stderr");
	if (ft_strcmp(test, "2"))
	{
		close(2);
		return_back_fd(test);
		VAR->add_bout("hidden", "stdin", "2");
	}
}

int		execution(t_leaf *branche, int *redir_process, int pipe_g)
{
	int		count;
	t_ast	*ast;
	pid_t	pid;

	ast = branche->content;
	if (ast->argv)
		VAR->add_bout("env", "_", *ast->argv);
	if (!ast->flag)
	{
		if (!built_in_before_fork(ast))
			return (0);
		pid = fork();
		if (pid == -1)
		{
			erreur(SHELL, "fork", "echec du process");
			return (1);
		}
		if (pid == 0)
		{
			if (redir_process && *(redir_process + 2))
				dup2(*(redir_process + 1), atoi(VAR->chop("hidden", "stdout")));
			if (redir_process && !pipe_g)
				dup2(*redir_process, atoi(VAR->chop("hidden", "stdin")));
			if (open_file(ast->redir, ast->argv))
				exit (1);

			if (ast->argv && built_in(ast))
				count = 0;
			else if (ast->argv || (count = 0))
			{
				VAR->add_bout("env", "_", *(ast->argv));
				if (ft_strchr(*(ast->argv), '/'))
					count = new_process(ast, "no such file or directory", redir_process);
				else
					count = exe_path(ast->argv, ast, redir_process);
			}
			else
				ft_lstiter(ast->redir, redirpass);
			//	ft_putnbr(((t_redir *)ast->redir->content)->in);
			close_file(ast->redir);
			exit(count);
		}
		if (pid && !(redir_process && *(redir_process + 2)))
		{
			if (redir_process)
				while((--*(redir_process + 3)) != -1)
					waitpid(-1, &count, 0);
			waitpid(pid, &count, 0);
		}
		//wait(&count);
		return (WEXITSTATUS(count));
	}
	else if (ast->flag)
		exec_sparator(branche, redir_process);
	return (1);
}
