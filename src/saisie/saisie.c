/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   saisie.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 21:24:32 by tdumouli          #+#    #+#             */
/*   Updated: 2017/09/21 06:37:59 by tdumouli         ###   ########.fr       */
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
	write(fd, blk->str + i - j, j);// + (*(blk->str + i - j) == '\n'), j);
	write(1, " ", 1);
	//if ((j != i && !(j % w.ws_col)) || (i == j && j + blk->pos_start ==  w.ws_col))
	//	write(1, "\r\n", 2);
}

static void			lecture_autre(int lec, char *c, t_data *my_block)
{
	if (lec == 3 && *c == 27)
		move_simple(c, my_block);
	else if (lec == 4 && *c == 27)
		move_simple_depl(c, my_block);
	else if (*c == -30 || *c == -61)
		cutpaste(c, my_block);
}

char				*lecture(t_data *my_block)
{
	char	c[1024];
	int		lec;

	while ((lec = read(0, c, 1024)) > 0)
	{
		*(c + lec) = 0;
		if (*(c) == 3)
			return (NULL);
		if (*(c) == 13 && *(my_block->str + my_block->len - 1) == '\\')
		{
			clean(my_block);
			my_block->pointeur = my_block->len;
			*(my_block->str + my_block->len - 1) = '\n';
			ft_write(1, my_block);
		}
		else if (*(c) == 13 || *c == 4)
			return (set_hist(my_block->str, *c));
		if (31 < *c || *c == '\n')
			ajout_str(c, my_block);
		else
			lecture_autre(lec, c, my_block);
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

char				*saisie(void)
{
	t_data			*my_block;
	struct termios	term;
	char			*read;

	read = NULL;
	if (!isatty(0))
	{
		read = alloc_brute_to_fd(0);
		execmain(read);
		exit(0);
	}
	if (tcgetattr(0, &term) == -1)
		return (0);
	write(1, "\r🦄 > \x1b[39m", 13);
	if (!(my_block = t_dat_init()))
		return (NULL);
	if (pass_canonique())
		return (NULL);
	read = lecture(my_block);
	if (tcsetattr(0, 0, &term) == -1)
		return (NULL);
	write(1, "\n", 1);
	free(my_block);
	return (read);
}
