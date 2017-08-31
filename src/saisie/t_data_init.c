/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_data_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 22:19:59 by tdumouli          #+#    #+#             */
/*   Updated: 2017/05/24 22:20:00 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "g.h"

t_data			*t_dat_init(void)
{
	t_data	*ret;

	if (!(ret = malloc(sizeof(t_data))))
		return (NULL);
	if (!(ret->str = malloc(sizeof(char))))
	{
		free(ret);
		return (NULL);
	}
	*(ret->str) = 0;
	ret->len = 0;
	ret->pointeur = 0;
	ret->pos_start = 3;
	return (ret);
}
