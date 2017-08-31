/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grsa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 16:30:08 by tdumouli          #+#    #+#             */
/*   Updated: 2017/08/31 04:05:21 by tdumouli         ###   ########.fr       */
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
	int i;

	i = 0;
	while (*(*s + i))
	{
		if (*(*s + i) == '$' && *(*s + i + 1))
			i += variable(s, i);
		else if (!flagcote && i == 0 && VAR->chop("alias", *s) && !test)
			copy(s, 0, VAR->chop("alias", *s), ft_strlen(*s));
		else if (*(*s + i) == '*')
			++i;
		else
			++i;
	}
}

void	open_file(t_list *redir_start)
{
	int open_flag;

	while (redir_start)
	{
		//ft_putnbr(((t_redir *)redir_start->content)->in);
		//ft_putnbr(((t_redir *)redir_start->content)->out);
		//write(1, ((t_redir *)redir_start->content)->tok->start,
	//	((t_redir *)redir_start->content)->tok->len);
		if (((t_redir *)redir_start->content)->out <= -1)
		{
		//ft_putstr(((t_redir *)redir_start->content)->file);
			if (*((t_redir *)redir_start->content)->tok->start == '<')
			{
				if (*(((t_redir *)redir_start->content)->tok->start + 1) == '<')
				{
					write(2, "tamere", 6);
					//get_next line ou termcaps
				}
				else
				{
					((t_redir *)redir_start->content)->out = 
	((t_redir *)redir_start->content)->in;
					if((((t_redir *)redir_start->content)->in = open(
	((t_redir *)redir_start->content)->file, O_RDONLY|O_NOCTTY)) < 0)
						{
							write(1, "ouvrepas", 8);
							return ;
						}
					((t_redir *)redir_start->content)->fd =
	((t_redir *)redir_start->content)->in;

					dup2(((t_redir *)redir_start->content)->in,
					((t_redir *)redir_start->content)->out);//test dup2
					
				}
			}
			else if (*((t_redir *)redir_start->content)->tok->start == '>')
			{
				open_flag = (*(((t_redir *)redir_start->content)
   ->tok->start + 1) != '>') ? O_TRUNC : O_APPEND;	
				//ft_putnbr(open_flag);
				if (!((((t_redir *)redir_start->content)->out = 
			open(((t_redir *)redir_start->content)->file,
O_CREAT | O_WRONLY | open_flag, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) > 0))
					return ;
					((t_redir *)redir_start->content)->fd =
	((t_redir *)redir_start->content)->out;
			}
		
		}
		//write(1, "\n", 1);
		//ft_putnbr(((t_redir *)redir_start->content)->in);
		//write(1, "->", 2);
		//ft_putnbr(((t_redir *)redir_start->content)->out);
		//write(1, "\n", 1);
		dup2(((t_redir *)redir_start->content)->out,
					((t_redir *)redir_start->content)->in);//test dup2
		redir_start = redir_start->next;
	}
}

int		new_process(t_ast	*ast, char **av, char *error)  //changer av par ast
{
	pid_t	pid;
	int		count;

/*	if (!is_dir(*av))
	{
		cd(*av);
		return (EXIT_SUCCESS);
	}*/
	(void)ast;
	if (!access(*av, X_OK))
	{
		pid = fork();
		if (pid == 0)
		{
		open_file(ast->redir);
			execve(*av, av, VAR->chop_all("env"));
		}
		wait(&count);
		return (WEXITSTATUS(count));
	}
	erreur(SHELL, error, *av);
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
			j = new_process(ast, av, "command not found");
		freeteuse((void **)path, 1);
	}
	return (j);
}

int		*fume_pipe()
{
	//static int	next_out = 0;
	int			*pipe_ret;

	pipe_ret = (int *)malloc(sizeof(int) * 3);
	if(pipe(pipe_ret))
	{
		write(2, "Erreur de création du tube.\n", 20);
		return (NULL);
	}
	*(pipe_ret + 2) = -1;
	//next_out = *pipe_ret;
	return (pipe_ret);
}


int		execution(t_leaf *branche, int *f);
void	exec_sparator(t_leaf *branche, int *redir_process_du_futur)
{
	t_token	*tok;
	int		ret_branche;
	int		*redir_process;
	
	redir_process = NULL;
	tok = ((t_ast *)branche->content)->tok;
	if (tok->len == 1 && *tok->start == '|')
		redir_process = fume_pipe();
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
	//i = -1;
	//	change((av + i));
	if (!ast->flag && ast->argv)	//commande
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
			count = new_process(ast, (ast->argv), "no such file or directory");
		else
			count = exe_path(ast->argv, ast);
		//close (1);
		exit (count);
		}
		wait(&count);
		return (WEXITSTATUS(count));
	}
	else if (ast->flag)
		exec_sparator(branche, redir_process);
	return (1);
}
