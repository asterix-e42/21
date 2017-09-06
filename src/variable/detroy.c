/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detroy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/16 14:14:45 by tdumouli          #+#    #+#             */
/*   Updated: 2017/09/06 01:39:46 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "tent.h"
#include "libft.h"

static void		del_private(void *priv, size_t pk)
{
	(void)pk;
	if (((t_private *)priv)->name)
		free(((t_private *)priv)->name);
	if (((t_private *)priv)->value)
		free(((t_private *)priv)->value);
	free(priv);
}

static void		del_var(void *priv, size_t pk)
{
	(void)pk;
	free(((t_var *)priv)->name);
	ft_lstdel(&((t_var *)priv)->privat, del_private);
	free(priv);
}

static void		destroy_var(char *nam_var)
{
	t_var		*tmp;
	t_list		*exist;
	t_list		**are_you;

	are_you = (t_list **)all_var(734);
	tmp = ft_lstfind_var(nam_var);
	if (tmp)
	{
		if (tmp != (t_var *)(*are_you)->content)
		{
			while (tmp != (t_var *)(*are_you)->next->content)
				*are_you = (*are_you)->next;
		}
		exist = *are_you;
		if (tmp == exist->content)
			*are_you = exist->next;
		else
		{
			exist = exist->next;
			(*are_you)->next = exist->next;
		}
		ft_lstdelone(&exist, del_var);
	}
}

void			destroy(char *nam_var, char *name_priv)
{
	t_var		*tmp;
	t_list		*exist;
	t_list		*are_you;

	if (!name_priv)
	{
		destroy_var(nam_var);
		return ;
	}
	are_you = *(t_list **)all_var(734);
	tmp = ft_lstfind_var(nam_var);
	if (tmp &&
	(exist = ft_lstfind_priv(name_priv, tmp->privat)))
	{
		are_you = tmp->privat;
		if (exist == are_you)
			tmp->privat = exist->next;
		else
			while (exist != (are_you)->next)
				are_you = (are_you)->next;
		are_you->next = exist->next;
		ft_lstdelone(&exist, del_private);
	}
}
