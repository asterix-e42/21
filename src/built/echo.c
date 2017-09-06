/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 01:50:03 by tdumouli          #+#    #+#             */
/*   Updated: 2017/09/06 02:13:51 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_echo(char **av)
{
	if (!*(av + 1))
		write(1, "\n", 1);
	else
		while (*(++av))
			ft_putendl(*av);
}
