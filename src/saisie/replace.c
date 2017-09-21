/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/01 10:06:07 by tdumouli          #+#    #+#             */
/*   Updated: 2017/09/21 05:23:09 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "g.h"
#include "libft.h"
#include <stdlib.h>

void	replace(t_data *my_block, char *new)
{
	if (!new)
		return ;
	clean(my_block);
	free(my_block->str);
	my_block->str = ft_strdup(new);
	my_block->len = ft_strlen(new);
	my_block->pointeur = my_block->len;
	ft_write(1, my_block);
	point(my_block, 1);
}

void	ajout_str(char *c, t_data *my_block)
{
	clean(my_block);
//	sleep(1);
	if (*c == 127)
		ft_alloc(my_block, NULL);
	else if (my_block->len + ft_strlen(c) < SIZE_WRITE)
		ft_alloc(my_block, c);
//	sleep(1);
	ft_write(1, my_block);
//	sleep(1);
	point(my_block, 1);
}

void	cutpaste(char *c, t_data *blk)
{
	if (*c == -30 && *(c + 1) == -119 && *(c + 2) == -120)
	{
		cutinhist("paste", blk->str);
		replace(blk, "");
	}
	if (*c == -30 && *(c + 1) == -120 && *(c + 2) == -102)
		ajout_str(fleme(), blk);
	if (*c == -61 && *(c + 1) == -89)
		cutinhist("paste", blk->str);
}
