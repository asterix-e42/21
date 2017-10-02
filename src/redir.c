/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/02 20:19:34 by tdumouli          #+#    #+#             */
/*   Updated: 2017/10/02 16:23:30 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "mini.h"

void		pass(int fd_read, int fd_write)
{
	char		str[BUFF_SIZE + 1];
	int			len_read;

	while ((len_read = read(fd_read, str, BUFF_SIZE)) > 0)
	{
		*(str + len_read) = '\0';
		write(fd_write, str, ft_strlen(str));
	}
	close(fd_write);
}

void		redirpass(t_list *elem)
{
	t_redir		*ast;

	ast = elem->content;
	if (ast->in == 1)
		ast->in = 0;
	pass(ast->in, ast->out);
}

void		d_redir_g(t_redir *redir, char *flag_av)
{
	char	*str;
	int		*fd;

	fd = fume_pipe();
	redir->out = redir->in;
	while (get_next_line(0, &str))
	{
		if (!ft_strcmp(str, redir->file))
			break ;
		ft_putstr_fd(str, (*(fd + 1)));
		ft_putchar_fd('\n', (*(fd + 1)));
	}
	close(*(fd + 1));
	if (!flag_av)
		redir->in = *fd;
	else
		dup2(*fd, redir->in);
}
