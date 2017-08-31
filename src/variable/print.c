/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/16 14:23:53 by tdumouli          #+#    #+#             */
/*   Updated: 2017/04/17 17:30:09 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tent.h"
#include "libft.h"

static void	print_elm(t_list *list)
{
	ft_putstr(((t_private *)list->content)->name);
	ft_putchar('=');
	ft_putstr(((t_private *)list->content)->value);
	ft_putchar('\n');
}

void		print(char *nam_var, char *name_priv)
{
	t_var		*tmp;
	t_list		*exist;

	tmp = ft_lstfind_var(nam_var);
	if (tmp)
	{
		if (name_priv)
		{
			if ((exist = ft_lstfind_priv(name_priv, tmp->privat)))
				print_elm(exist);
		}
		else
			ft_lstiter((tmp->privat), print_elm);
	}
}
