/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/16 14:33:56 by tdumouli          #+#    #+#             */
/*   Updated: 2017/09/01 07:15:34 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "tent.h"
#include "libft.h"

t_var		*ft_lstfind_var(char *nam)
{
	t_list	*are_you;

	are_you = *(t_list **)all_var(734);
	while (are_you && ft_strcmp(((t_var *)are_you->content)->name, nam))
		are_you = are_you->next;
	if (are_you)
		return (((t_var *)are_you->content));
	return (NULL);
}

t_list		*ft_lstfind_priv(char *nam, t_list *are_you)
{
	while (are_you && ft_strcmp(((t_private *)are_you->content)->name, nam))
		are_you = are_you->next;
	if (are_you)
		return (are_you);
	return (NULL);
}

t_function	*all_var(int choix)
{
	static t_the_one_struct	*ring = NULL;

	if (!ring)
	{
		if (!(ring = (t_the_one_struct *)malloc(sizeof(t_the_one_struct))))
			return (NULL);
		if (!(ring->fun = (t_function *)malloc(sizeof(t_function))))
		{
			free(ring);
			ring = NULL;
			return (NULL);
		}
		ring->fun->init = init_var;
		ring->fun->print = print;
		ring->fun->add = add;
		ring->fun->add_bout = add_bout;
		ring->fun->chop = chop;
		ring->fun->chop_all = chop_all;
		ring->fun->unset = destroy;
		ring->var = NULL;
	}
	if (!choix)
		return (ring->fun);
	else
		return ((t_function *)&(ring->var));
}
