/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/01 06:18:13 by tdumouli          #+#    #+#             */
/*   Updated: 2017/09/24 03:46:40 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*get_hist(int up)
{
	char	*comp;
	char	*str_ret;

	comp = ft_itoa(ft_atoi(VAR->chop("hidden", "comp")) + up);
	str_ret = VAR->chop("hist", comp);
	if (!str_ret)
	{
		free(comp);
		write(1, "\a", 1);
		return (NULL);
	}
	VAR->add_bout("hidden", "comp", comp);
	free(comp);
	return (str_ret);
}

char	*set_hist(char *str, char c)
{
	char	*rang;

	rang = VAR->chop("hidden", "rang");
	if (str && *str)
	{
		VAR->add_bout("hist", rang, str);
		rang = ft_itoa(ft_atoi(rang) + 1);
		VAR->add_bout("hidden", "rang", rang);
		VAR->add_bout("hidden", "comp", rang);
		free(rang);
	}
	else if (c == 4)
		str = "exit";
	else
		VAR->add_bout("hidden", "comp", rang);
	return (str);
}

void	cutinhist(char *pas, char *nam)
{
	VAR->add_bout("hidden", pas, nam);
}

char	*fleme(void)
{
	char	*tmp;

	tmp = VAR->chop("hidden", "paste");
	if (!tmp)
		return ("");
	return (tmp);
}
