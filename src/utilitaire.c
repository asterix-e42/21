/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilitaire.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 15:29:31 by tdumouli          #+#    #+#             */
/*   Updated: 2017/09/26 19:35:21 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "mini.h"

char	*ft_strjoini(char const *s1, char const *s2, char c)
{
	char	*ret;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	if (!(ret = (char *)malloc(sizeof(char) * (i + j + 2))))
		return (NULL);
	*(ret + i + j + 1) = '\0';
	while (j--)
		*(ret + i + j + 1) = *(s2 + j);
	*(ret + i) = c;
	while (i--)
		*(ret + i) = *(s1 + i);
	return (ret);
}

void	erreur(char *where, char *error, char *what)
{
	ft_putstr_fd(where, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error, 2);
	if (what)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(what, 2);
		ft_putchar_fd('\n', 2);
	}
}

void	whereareyou(char *name)
{
	char	tmp[1024];

	if (!getcwd(tmp, 1024))
		return ;
	VAR->add_bout("env", name, tmp);
}

void	freeteuse(void **s, int niveau)
{
	int		i;

	i = -1;
	if (!s)
		return ;
	if (niveau)
		while (*(s + ++i))
			freeteuse((void **)*(s + i), niveau - 1);
	free(s);
	s = NULL;
}

int		supersplit(char ****ret, char *av, char s1, char s2)
{
	char	**e1;
	int		size;

	if (!(e1 = ft_strsplit(av, s1)))
		return (1);
	size = -1;
	while (*(e1 + ++size))
		;
	if (!(*ret = (char ***)malloc(sizeof(char **) * (size + 1))))
	{
		freeteuse((void **)e1, 1);
		return (1);
	}
	*(*ret + size) = NULL;
	while (--size + 1)
		if (!(*(*ret + size) = ft_strsplit(*(e1 + size), s2)))
		{
			while (*(*ret + ++size))
				freeteuse((void **)(*ret + size), 2);
			freeteuse((void **)e1, 1);
			return (1);
		}
	freeteuse((void **)e1, 1);
	return (0);
}
