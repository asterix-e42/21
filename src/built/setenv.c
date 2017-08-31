/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 01:28:49 by tdumouli          #+#    #+#             */
/*   Updated: 2017/04/19 22:36:33 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mini.h"

void	ft_setenv(char **av, char *nam)
{
	int		i;
	i = 1;
	if (!*(av + 1))
		VAR->print(nam, NULL);
	else
		while (*(av + i))
		{
			VAR->add(nam, av + i, -1);
			++i;
		}
}
