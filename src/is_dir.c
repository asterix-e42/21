/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_dir.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 16:41:02 by tdumouli          #+#    #+#             */
/*   Updated: 2017/09/24 16:09:50 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

int		is_dir(char *name)
{
	struct stat		a;

	if (!name || !*name)
		return(3);
	if (stat(name, &a) < 0)
		return (1);
	if (S_ISDIR(a.st_mode))
		return (0);
	return (2);
}
