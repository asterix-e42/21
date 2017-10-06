/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 03:34:11 by tdumouli          #+#    #+#             */
/*   Updated: 2017/10/06 14:25:18 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mini.h"
#include <stdlib.h>

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
	t_redir	*redi;

	while (redir_start && (redi = ((t_redir *)redir_start->content)))
	{
		if (*redi->tok->start == '<')
		{
			if (redi_gauche(redi, flag_av))
				return (1);
		}
		else if (*redi->tok->start == '>')
			if (redi_droite(redi))
				return (1);
		if (flag_av)
			dup2(redi->out, redi->in);
		redir_start = redir_start->next;
	}
	return (0);
}

void	create_file(t_list *redir_start)
{
	t_redir	*redir;

	while (redir_start && (redir = ((t_redir *)redir_start->content)))
	{
		if (redir->out <= -1 && *redir->tok->start == '>')
			open(redir->file, O_CREAT | O_TRUNC | O_WRONLY,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		redir_start = redir_start->next;
	}
}

void	close_free(int **fd)
{
	close(**fd);
	free(*fd);
	*fd = NULL;
}
