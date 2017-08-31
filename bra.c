/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bra.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 18:52:31 by tdumouli          #+#    #+#             */
/*   Updated: 2017/04/20 20:25:55 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int		bra(char **av, char test, char *t1, char *t2)
{
	int		i;

	while (**av && !(i = 0))
	{
		if (**av == test)
			return (1);
		while (*(t1 + i) && *(t1 + i) != **av)
			++i;
		if (i != 3 && ++*av)
		{
			if (!bra(av, *(t2 + i), t1, t2))
				return (0);
		}
		else if (!(i = 0))
		{
			while (*(t2 + i) && *(t2 + i) != **av)
				++i;
			if (i != 3)
				return (0);
		}
		++*av;
	}
	return (test == 0);
}

int main(int ac, char **av)
{
	int i;

	i = 0;
	if (ac == 1)
		write(1, "\n", 1);
	while (++i != ac)
	{
		if (bra((av + i), 0, "[{(", "]})"))
			write(1, "OK\n", 3);
		else
			write(1, "Error\n", 6);
}}
