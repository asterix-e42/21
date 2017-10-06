/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 03:18:06 by tdumouli          #+#    #+#             */
/*   Updated: 2017/10/06 14:25:42 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mini.h"

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
	if (dup2(redi->out, redi->in) == -1)
	{
		erreur(SHELL, ft_itoa(redi->out), "bad file descriptor");
		return (1);
	}
	return (0);
}

int		redi_gauche(t_redir *redi, void *flag_av)
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
		if (!flag_av)
			redi->out = redi->in;
		if ((redi->fd = open(redi->file, O_RDONLY | O_NOCTTY)) < 0)
		{
			erreur(SHELL, "no such file or directory", redi->file);
			return (1);
		}
		if (flag_av)
			redi->out = redi->fd;
		else
			redi->in = redi->fd;
	}
	return (0);
}

int		redi_droite(t_redir *redi)
{
	int		open_fg;

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
	return (0);
}
