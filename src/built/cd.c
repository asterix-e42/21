/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 17:47:09 by tdumouli          #+#    #+#             */
/*   Updated: 2017/10/06 14:34:21 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include "libft.h"
#include "mini.h"
#include <stdlib.h>

void	pwd_short(char **pwd)
{
	int		writ;
	int		ber;
	int		flag;

	writ = 0;
	ber = 0;
	while (*(*pwd + ber) && !(flag = 0))
	{
		if (*(*pwd + ber) == '/' && *(*pwd + ber + 1) == '.')
		{
			if ((*(*pwd + ber + 2) == '/' || !*(*pwd + ber + 2)) && (flag = 1))
				ber += 2;
			else if (*(*pwd + ber + 2) == '.' &&
				(*(*pwd + ber + 3) == '/' || !*(*pwd + ber + 3)) && (flag = 1))
			{
				*(*pwd + writ) = '\0';
				writ = (writ < 1) ? 0 : ft_strrchr(*pwd, '/') - *pwd;
				ber += 3;
			}
		}
		if (!flag)
			*(*pwd + writ++) = *(*pwd + ber++);
	}
	*(*pwd + writ) = '\0';
	*(*pwd + writ - 1) = (*(*pwd + writ - 1) == '/') ? '\0' : (*pwd)[writ - 1];
}

char	*sesame(char *directory)
{
	struct stat		file_stat;

	if (stat(directory, &file_stat) < 0)
		return ("no such file or directory");
	else if (file_stat.st_mode & S_IXUSR)
		return (NULL);
	else
		return ("permission denied");
}

void	cd(char *av)
{
	char	*tmp;

	whereareyou("PWD");
	tmp = VAR->chop("env", "PWD");
	if ((av))
	{
		if (*(av) == '/')
			tmp = ft_strdup((av));
		else if (*(tmp) == '/' && !*(tmp + 1))
			tmp = ft_strjoini("", (av), '/');
		else
			tmp = ft_strjoini(tmp, (av), '/');
		pwd_short(&tmp);
		if (!*tmp && !(*(tmp + 1) = '\0'))
			*tmp = '/';
		if (sesame(tmp))
			erreur("cd", sesame(tmp), av);
		else
		{
			whereareyou("OLDPWD");
			VAR->add_bout("env", "PWD", tmp);
			chdir(tmp);
		}
		free(tmp);
	}
}

void	built_cd(char **av)
{
	char	*tmp;

	if (!*(av + 1))
		cd(VAR->chop("env", "HOME"));
	else if (!ft_strcmp(*(av + 1), "-"))
	{
		if (!(tmp = VAR->chop("env", "OLDPWD")))
			erreur(SHELL, "cd:", "OLDPWD not set");
		else
		{
			ft_putendl(tmp);
			cd(tmp);
		}
	}
	else
		cd((*(av + 1)));
}
