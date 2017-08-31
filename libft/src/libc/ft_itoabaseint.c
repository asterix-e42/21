/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoabaseint.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 05:05:40 by tdumouli          #+#    #+#             */
/*   Updated: 2016/12/20 07:12:46 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>
#include "libft.h"
#include <math.h>
#include <stdlib.h>

char	*ft_itoabaseint(unsigned int nb, char *b2)
{
	char				*ret;
	unsigned long int	tmp;
	size_t				size;
	int					skt;
	unsigned int		max;

	if (!b2 && !*b2 && !*(b2 + 1))
		return (0);
	tmp = nb;
	skt = 0;
	max = ft_strlen(b2);
	size = 1;
	while (tmp /= max)
		++size;
	ret = (char *)malloc(sizeof(char) * (size + 1));
	*(ret + size) = '\0';
	while (--size + 1)
	{
		*(ret + size) = *(b2 + (nb % max));
		nb /= max;
	}
	return (ret);
}
