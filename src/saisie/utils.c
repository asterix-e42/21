/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 22:15:16 by tdumouli          #+#    #+#             */
/*   Updated: 2017/05/24 22:15:42 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <term.h>
#include "g.h"
#include "libft.h"

int		ft_alloc(t_data *data, char *ajout)
{
	char	*tmp;

	tmp = data->str;
	if (ajout)
		data->len += ft_strlen(ajout);
	else
	{
		if (data->pointeur > 0 && --(data->pointeur) + 42)
			--(data->len);
		else
			return (0);
	}
	if (!(data->str = (char *)ft_memalloc(sizeof(char) * (data->len + 1))))
		return (-1);
	ft_strncpy(data->str, tmp, data->pointeur);
	if (ajout)
		ft_strcat(data->str, ajout);
	ft_strcat(data->str, tmp + data->pointeur + !(ajout));
	(data->pointeur) += (ajout) ? ft_strlen(ajout) : 0;
	*(data->str + data->len) = 0;
	free(tmp);
	return (0);
}

char	*recule(t_data *blk)
{
	char tmp;
	char *ret;

	tmp = *(blk->str + blk->pointeur);
	*(blk->str + blk->pointeur) = 0;
	ret = ft_strrchr(blk->str, '\n');
	*(blk->str + blk->pointeur) = tmp;
	return (ret);
}
