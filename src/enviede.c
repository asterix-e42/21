/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviede.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 01:58:11 by tdumouli          #+#    #+#             */
/*   Updated: 2017/04/19 15:08:16 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"
#include "libft.h"

void		lvlup(void)
{
	char *val;

	val = VAR->chop("env", "SHLVL");
	if (!val)
		VAR->add_bout("env", "SHLVL", "1");
	else
	{
		val = ft_itoa(ft_atoi(val) + 1);
		VAR->add_bout("env", "SHLVL", val);
		free(val);
	}
}
