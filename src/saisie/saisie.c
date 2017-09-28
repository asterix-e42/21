/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   saisie.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 21:24:32 by tdumouli          #+#    #+#             */
/*   Updated: 2017/09/28 01:19:13 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
#include <stdlib.h>
#include <unistd.h>
#include "g.h"
#include "libft.h"
#include <sys/ioctl.h>

void				ft_write(int fd, t_data *blk)
{
	int				i;
	int				j;
	struct winsize	w;

	ioctl(0, TIOCGWINSZ, &w);
	i = -1;
	j = -1;
	while (++j != -1 && ++i < blk->len)
	{
		if (*(blk->str + i) == '\n')
		{
			write(fd, blk->str + i - j, j + 1);
			j = -1;
			write(1, "\r", 1);
		}
	}
	write(fd, blk->str + i - j, j);
	write(1, " ", 1);
}

static void			lecture_autre(int lec, char *c, t_data *my_block)
{
	char	*tmp;

	if (31 < *c || *c == '\n')
	{
		if ((tmp = ft_strchr(c, 13)))
			*(tmp) = '\0';
		ajout_str(c, my_block);
		if (tmp)
			*tmp = 13;
	}
	else if (lec == 3 && *c == 27)
		move_simple(c, my_block);
	else if (lec == 4 && *c == 27)
		move_simple_depl(c, my_block);
	else if (*c == -30 || *c == -61)
		cutpaste(c, my_block);
}

char				*lecture(t_data *my_block, int contrd)
{
	char	c[1024];
	int		lec;
	char	*returnlign;
	char	*tmp;

	tmp = NULL;
	while (tmp || (lec = read(0, c, 1024)) > 0)
	{
		if (!tmp)
			returnlign = c;
		else
			returnlign = tmp;
		*(c + lec) = 0;
		if (*(returnlign) == 3)
			return (ft_strdel(&my_block->str));
		if (*(returnlign) == 13 && *(my_block->str + my_block->len - 1) == '\\')
			*returnlign = '\n';
		else if (*(returnlign) == 13)
			return (my_block->str);
		else if ((*returnlign == 4 && contrd))
			return ((*my_block->str) ? my_block->str : ft_strdup("exit"));
		lecture_autre(lec, returnlign, my_block);
	}
	return (my_block->str);
}

char				*alloc_brute_to_fd(int fd)
{
	char			buf[BUFF_SIZE + 1];
	int				rd;
	char			*ret;
	char			*tmp;

	ret = NULL;
	while ((rd = read(fd, buf, BUFF_SIZE)))
	{
		if (rd == -1)
			return (ret);
		*(buf + rd) = '\0';
		if (!ret)
			ret = ft_strdup(buf);
		else
		{
			tmp = ret;
			ret = ft_strjoin(ret, buf);
			free(tmp);
		}
	}
	return (ret);
}

char				*saisie(char *promt, int contrd)
{
	t_data			*my_block;
	struct termios	term;
	char			*read;

	if (!isatty(0))
	{
		if (get_next_line(0, &read) > 0)
			execmain(read);
		exit(0);
	}
	if (tcgetattr(0, &term) == -1)
		return (0);
	write(1, "\r", 1);
	write(1, promt, ft_strlen(promt));
	write(1, "> \x1b[39m", 7);
	if (!(my_block = t_dat_init(promt)))
		return (NULL);
	if (pass_canonique())
		return (NULL);
	read = lecture(my_block, contrd);
	if (tcsetattr(0, 0, &term) == -1)
		return (NULL);
	write(1, "\n", 1);
	free(my_block);
	return (read);
}
