/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_deplacement.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 22:20:38 by tdumouli          #+#    #+#             */
/*   Updated: 2017/09/28 01:45:20 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "g.h"
#include "libft.h"
#include <sys/ioctl.h>

void			yolo(int dir, int y)
{
	char			depl[3];

	*(depl) = 27;
	*(depl + 1) = 91;
	*(depl + 2) = dir;
	while (--y > -1)
		write(1, depl, 3);
}

static int		depl_y(int pos, t_data *blk)
{
	int				ret;
	struct winsize	w;
	char			*verrif[2];

	ioctl(0, TIOCGWINSZ, &w);
	ret = ft_strcpt(blk->str, '\n') - ft_strcpt(blk->str + pos, '\n');
	*(verrif) = blk->str;
	while ((*(verrif + 1) = ft_strchr(*verrif, '\n')))
	{
		if (*(verrif + 1) - blk->str >= pos)
			break ;
		if (*verrif == blk->str && (*(verrif + 1) - *verrif - 1) /
				(w.ws_col - blk->pos_start) && ++ret)
			*verrif += (w.ws_col - blk->pos_start);
		ret += (*(verrif + 1) - *verrif) / (w.ws_col);
		*(verrif) = *(verrif + 1) + 1;
	}
	if (*verrif == blk->str && pos / (w.ws_col - blk->pos_start))
	{
		++ret;
		pos -= (w.ws_col - blk->pos_start);
	}
	ret += (blk->str - *verrif + pos) / w.ws_col;
	return (ret);
}

void			start_lec(int pos, t_data *blk)
{
	write(1, "\r", 1);
	yolo(67, blk->pos_start);
	yolo(65, depl_y(pos, blk));
}

void			point(t_data *blk, int fg)
{
	int				depl_;
	struct winsize	w;

	ioctl(0, TIOCGWINSZ, &w);
	depl_ = depl_y(blk->pointeur, blk);
	if (fg)
		start_lec(blk->len, blk);
	if (recule(blk))
	{
		yolo(66, depl_);
		write(1, "\r", 1);
		yolo(67, (blk->pointeur + blk->str - recule(blk) - 1) % w.ws_col);
	}
	else
	{
		yolo(66, depl_);
		if (depl_)
		{
			write(1, "\r", 1);
			yolo(67, blk->pointeur + blk->pos_start - depl_ * w.ws_col);
		}
		else
			yolo(67, blk->pointeur);
	}
}

void			clean(t_data *blk)
{
	int				i;

	i = -1;
	start_lec(blk->pointeur, blk);
	while (++i < blk->len + 1)
	{
		if (*(blk->str + i) == '\n')
			write(1, "\n\r", 2);
		write(1, " ", 1);
	}
	start_lec(blk->len, blk);
}
