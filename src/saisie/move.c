/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 21:26:15 by tdumouli          #+#    #+#             */
/*   Updated: 2017/09/20 23:41:43 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "g.h"
#include "libft.h"

void			move_sec_depl(char *s, t_data *blk)
{
	if (*(s + 2) == 68)
	{
		if (blk->pointeur > 0)
			set_t_data_pointeur(blk, -1);
		while (blk->pointeur > 0 && *(blk->str + blk->pointeur) == ' ')
			set_t_data_pointeur(blk, -1);
		while (blk->pointeur > 0 && !ft_isspace(*(blk->str + blk->pointeur)))
			set_t_data_pointeur(blk, -1);
		return ;
	}
	if (*(s + 2) == 67)
	{
		if (blk->pointeur < blk->len)
			set_t_data_pointeur(blk, 1);
		while (blk->pointeur < blk->len && *(blk->str + blk->pointeur) == ' ')
			set_t_data_pointeur(blk, 1);
		while (blk->pointeur < blk->len &&
				!ft_isspace(*(blk->str + blk->pointeur)))
			set_t_data_pointeur(blk, 1);
	}
}

/*
** 67 -> rigth
** 68 -> left
** 65 -> move_simple
** 66 -> down
*/

static int		move_sec(t_data *blk, char *s, int start)
{
	char	*tmp;
	int		len;

	if (*(s + 2) == 65)
	{
		tmp = recule(blk);
		if (!tmp)
			return (0 - blk->pointeur);
		set_t_data_pointeur(blk, 0 - start);
		len = (recule(blk)) ? recule(blk) - tmp : blk->str - tmp - 1;
		len += MIN(0 - len, start);
		return (len);
	}
	if (*(s + 2) == 66)
	{
		tmp = ft_strchr(blk->str + blk->pointeur, '\n');
		if (!tmp)
			return (blk->len - blk->pointeur);
		len = (ft_strchr(tmp + 1, '\n')) ? MIN(ft_strchr(tmp + 1, '\n')
				- tmp, start) : MIN(start, (int)ft_strlen(tmp));
		return (tmp - blk->str - blk->pointeur + len);
	}
	return (0);
}

void			move_simple_depl(char *s, t_data *blk)
{
	++s;
	if (*s == 27 && *(s + 1) == 91)
	{
		if (*(s + 2) == 67)
			move_sec_depl(s, blk);
		else if (*(s + 2) == 68)
			move_sec_depl(s, blk);
		else if (recule(blk))
			set_t_data_pointeur(blk,
				move_sec(blk, s, blk->str + blk->pointeur - recule(blk)));
		else
			set_t_data_pointeur(blk, move_sec(blk, s, blk->pointeur + 1));
	}
}

void			move_simple(char *s, t_data *blk)
{
	if (*s == 27 && *(s + 1) == 91)
	{
		if (*(s + 2) == 72)
			set_t_data_pointeur(blk, 0 - blk->pointeur);
		if (*(s + 2) == 70)
			set_t_data_pointeur(blk, blk->len - blk->pointeur);
		if (*(s + 2) == 65)
			replace(blk, get_hist(-1));
		else if (*(s + 2) == 66)
			replace(blk, get_hist(1));
		else if (*(s + 2) == 67)
		{
			if (blk->pointeur < blk->len)
				set_t_data_pointeur(blk, 1);
		}
		else if (*(s + 2) == 68)
		{
			if (blk->pointeur > 0)
				set_t_data_pointeur(blk, -1);
		}
	}
}
