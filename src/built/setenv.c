/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 01:28:49 by tdumouli          #+#    #+#             */
/*   Updated: 2017/09/06 01:55:06 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mini.h"

void	ft_setenv(t_ast *ast)
{
	int		i;
	char	*nam;

	if (!(nam = VAR->chop(*ast->argv + 3, 0)))
		return ;
	i = 0;
	if (!(ast->assign))
	{
		VAR->print(nam, NULL);
	}
	else
	{
		while (*(ast->assign + i))
		{
			VAR->add(nam, ast->assign + i, -1);
			++i;
		}
	}
}
