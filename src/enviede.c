/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviede.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 01:58:11 by tdumouli          #+#    #+#             */
/*   Updated: 2017/09/23 22:05:13 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"
#include "libft.h"

void		lvlup(char *env, char *lvl)
{
	char *val;

	val = VAR->chop(env, lvl);
	if (!val)
		VAR->add_bout(env, lvl, "1");
	else
	{
		val = ft_itoa(ft_atoi(val) + 1);
		VAR->add_bout(env, lvl, val);
		free(val);
	}
}
