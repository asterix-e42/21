/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   saisie.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 21:24:32 by tdumouli          #+#    #+#             */
/*   Updated: 2017/09/02 18:40:30 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <term.h>
#include "g.h"
#include "libft.h"

void				ft_write(int fd, char *str, int len)
{
	int		i;
	int		j;

	i = -1;
	j = -1;
	while (++j != -1 && ++i < len)
	{
		if (*(str + i) == '\n')
		{
			write(fd, str + i - j, j + 1);
			j = -1;
			write(1, "\r", 1);
		}
	}
	write(fd, str + i - j + (*(str + i - j) == '\n'), j);
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
		if (*(c) == 13 || *c == 4)
			return (set_hist(my_block->str, *c));
		if (31 < *c || *c == '\n')
			ajout_str(c, my_block);
		else
			lecture_autre(lec, c, my_block);
	}
	return (my_block->str);
}

char				*saisie(void)
{
	t_data			*my_block;
	struct termios	term;
	char			*read;

	if (tcgetattr(0, &term) == -1)
		return (NULL);
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
