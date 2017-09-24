/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_data_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 22:19:59 by tdumouli          #+#    #+#             */
/*   Updated: 2017/09/23 22:38:46 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "g.h"
#include "libft.h"

t_data			*t_dat_init(char *promt)
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
	if (!ft_strcmp(promt, "🦄 "))
		ret->pos_start = 4;
	else
		ret->pos_start = 2 + ft_strlen(promt);
	return (ret);
}
