/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grsa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 16:30:08 by tdumouli          #+#    #+#             */
/*   Updated: 2017/09/01 12:54:55 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "mini.h"
#include "lexer.h"

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
			;
		++i;
	}
}

void	open_file(t_list *redir_start)
{
	int open_flag;

	while (redir_start)
	{
		if (((t_redir *)redir_start->content)->out <= -1)
		{
			if (*((t_redir *)redir_start->content)->tok->start == '<')
				if (*(((t_redir *)redir_start->content)->tok->start + 1) == '<')
				{
					write(2, "tamere", 6);
					//get_next line ou termcaps
				}
				else
				{
					((t_redir *)redir_start->content)->out =
	((t_redir *)redir_start->content)->in;
					if ((((t_redir *)redir_start->content)->in = open(
	((t_redir *)redir_start->content)->file, O_RDONLY | O_NOCTTY)) < 0)
					{
						write(1, "ouvrepas", 8);
						return ;
					}
					((t_redir *)redir_start->content)->fd =
	((t_redir *)redir_start->content)->in;
					dup2(((t_redir *)redir_start->content)->in,
					((t_redir *)redir_start->content)->out);
				}
			else if (*((t_redir *)redir_start->content)->tok->start == '>')
			{
				open_flag = (*(((t_redir *)redir_start->content)
							->tok->start + 1) != '>') ? O_TRUNC : O_APPEND;
				if (!((((t_redir *)redir_start->content)->out =
			open(((t_redir *)redir_start->content)->file,
O_CREAT | O_WRONLY | open_flag, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) > 0))
					return ;
				((t_redir *)redir_start->content)->fd =
	((t_redir *)redir_start->content)->out;
			}
		}
		dup2(((t_redir *)redir_start->content)->out,
					((t_redir *)redir_start->content)->in);
		redir_start = redir_start->next;
	}
}

void	create_file(t_list *redir_start)
{
	int		open_close;

	while (redir_start)
	{
		if (((t_redir *)redir_start->content)->out <= -1 &&
			*((t_redir *)redir_start->content)->tok->start == '>')
			if (((open_close = open(((t_redir *)redir_start->content)->file,
	O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) > 0))
				close(open_close);
		redir_start = redir_start->next;
	}
}

int		new_process(t_ast *ast, char *error)
{
	pid_t	pid;
	int		count;

	(void)ast;
	if (!access(*(ast->argv), X_OK))
	{
		pid = fork();
		if (pid == 0)
		{
			open_file(ast->redir);
			execve(*(ast->argv), ast->argv, VAR->chop_all("env"));
		}
		wait(&count);
		return (WEXITSTATUS(count));
	}
	erreur(SHELL, error, *(ast->argv));
	return (1);
}

int		built_in(char **av)
{
	char	*s;

	if (!*av)
		return (1);
	if (!ft_strcmp(*av, "cd"))
		built_cd(av);
	else if (VAR->chop(*av, 0))
		VAR->print(*av, NULL);
	else if (!ft_strncmp(*av, "set", 3) && *(s = *av + 3) && VAR->chop(s, 0))
		ft_setenv(av, s);
	else if (!ft_strcmp(*(av), "exit"))
		ft_mini_exit(av);
	else if (!ft_strncmp(*av, "unset", 5) && *(s = *av + 5) && VAR->chop(s, 0))
		while (*(++av))
			VAR->unset(s, *av);
	else if (!ft_strcmp(*av, "echo"))
		ft_echo(av);
	else
		return (0);
	while (*(av))
		++av;
	VAR->add_bout("env", "_", *(av - 1));
	return (1);
}

int		exe_path(char **av, t_ast *ast)
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
			j = new_process(ast, "command not found");
		freeteuse((void **)path, 1);
	}
	return (j);
}

int		*fume_pipe(void)
{
	int			*pipe_ret;

	pipe_ret = (int *)malloc(sizeof(int) * 3);
	if (pipe(pipe_ret))
	{
		write(2, "Erreur de création du tube.\n", 20);
		return (NULL);
	}
	*(pipe_ret + 2) = -1;
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
	ret_branche = execution(branche->gauche, redir_process);
	if (redir_process)
	{
		close(*(redir_process + 1));
		if (redir_process_du_futur)
			*(redir_process + 1) = *(redir_process_du_futur + 1);
		else
			*(redir_process + 2) = 0;
	}
	if (tok->len == 1 || ret_branche == (*tok->start == '|') ||
						!ret_branche == (*tok->start == '&'))
		execution(branche->droite, redir_process);
	if (redir_process)
		free(redir_process);
}

int		execution(t_leaf *branche, int *redir_process)
{
	int		count;
	t_ast	*ast;
	pid_t	pid;

	ast = branche->content;
	if (!ast->flag && ast->argv)
	{
		if (built_in(ast->argv))
			return (0);
		pid = fork();
		if (pid == 0)
		{
			open_file(ast->redir);
			if (redir_process && *(redir_process + 2))
				dup2(*(redir_process + 1), 1);
			if (redir_process)
				dup2(*redir_process, 0);
			VAR->add_bout("env", "_", *(ast->argv));
			if (ft_strchr(*(ast->argv), '/'))
				count = new_process(ast, "no such file or directory");
			else
				count = exe_path(ast->argv, ast);
			exit(count);
		}
		wait(&count);
		return (WEXITSTATUS(count));
	}
	else if (ast->flag)
		exec_sparator(branche, redir_process);
	return (1);
}
