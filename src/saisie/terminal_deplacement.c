/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_deplacement.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 22:20:38 by tdumouli          #+#    #+#             */
/*   Updated: 2017/05/24 22:20:48 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "g.h"
#include "libft.h"

void			yolo(int dir, int y)
{
	char	depl[3];

	*(depl) = 27;
	*(depl + 1) = 91;
	*(depl + 2) = dir;
	while (--y > -1)
		write(1, depl, 3);
}

static void		start_lec(int pos, t_data *blk)
{
	write(1, "\r", 1);
	yolo(67, blk->pos_start);
	yolo(65, ft_strcpt(blk->str, '\n') - ft_strcpt(blk->str + pos, '\n'));
}

void			point(t_data *blk, int fg)
{
	if (fg)
		start_lec(blk->len, blk);
	if (recule(blk))
	{
		yolo(66, ft_strcpt(blk->str, '\n') -
				ft_strcpt(blk->str + blk->pointeur, '\n'));
		write(1, "\r", 1);
		yolo(67, blk->pointeur + blk->str - recule(blk) - 1);
	}
	else
		yolo(67, blk->pointeur);
}

void			set_t_data_pointeur(t_data *blk, int inc)
{
	start_lec(blk->pointeur, blk);
	blk->pointeur += inc;
	point(blk, 0);
}

void			clean(t_data *blk)
{
	int		i;

	i = -1;
	start_lec(blk->pointeur, blk);
	while (++i < blk->len)
	{
		if (*(blk->str + i) == '\n')
			write(1, "\n\r", 2);
		write(1, " ", 1);
	}
	start_lec(blk->len, blk);
}
