/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 16:19:35 by tdumouli          #+#    #+#             */
/*   Updated: 2017/10/04 22:44:18 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mini.h"
#include <stdlib.h>

void	change(char **s, int flagcote, char **test)
{
	int		i;
	char	*vr;

	i = 0;
	while (*(*s + i))
	{
		if (*(*s + i) == '$' && *(*s + i + 1))
			i += variable(s, i) - 1;
		else if (!flagcote && i == 0 && (vr = VAR->chop("alias", *s)) && !test)
		{
			i = copy(s, 0, vr, ft_strlen(*s)) - 1;
		}
		else if (*(*s + i) == '\\')
			i += echapement(s, i);
		else if (*(*s + i) == '*')
			i += 0;
		++i;
	}
}

int		copy(char **s, int symb, char *insert, int save_p)
{
	char	*tmp;
	int		ret;

	ret = ft_strlen(insert);
	tmp = *s;
	if (!(*s = ft_memalloc((1 + ft_strlen(*s) - save_p + ret))))
		return (0);
	ft_strncpy(*s, tmp, symb);
	ft_strcat(*s + symb, insert);
	ft_strcat(*s + symb + ft_strlen(insert), tmp + symb + save_p);
	free(tmp);
	return (ret);
}

int		insert_home(char **s, int symb)
{
	char	*envhome;
	int		size;
	char	*tmp;

	tmp = *s;
	if (*(*s + symb) != '~')
		return (2);
	envhome = VAR->chop("env", "HOME");
	if (!envhome)
		envhome = "/";
	size = ft_strlen(envhome);
	if (!(*s = ft_memalloc((ft_strlen(tmp) + size + 1))))
		return (1);
	ft_strcpy(*s + symb, envhome);
	ft_strcat(*s + symb + size, tmp + symb + 1);
	free(tmp);
	tmp = NULL;
	return (0);
}

int		echapement(char **s, int pos)
{
	char chang;

	chang = '\0';
	if (*(*s + pos + 1) == 'a')
		chang = '\a';
	else if (*(*s + pos + 1) == '\"')
		chang = '\"';
	else if (*(*s + pos + 1) == '\\')
		chang = '\\';
	else if (*(*s + pos + 1) == 'n' || !*(*s + pos + 1))
		chang = '\n';
	else if (*(*s + pos + 1) == 't')
		chang = '\t';
	if (chang)
	{
		*(*s + pos) = chang;
		if (*(*s + pos + 1))
			ft_strcpy((*s + pos + 1), (*s + pos + 2));
	}
	return (!chang);
}

int		variable(char **s, int symb)
{
	int		save_p;
	char	save_c;
	char	*chang;
	int		ret;

	save_p = 2;
	if (*(*s + symb + 1) == '$' && (save_c = *(*s + symb + 2)) + 1)
		chang = ft_itoa(getpid());
	else
	{
		while (*(*s + symb + save_p) && *(*s + symb + ++save_p) != '$')
			save_c = *(*s + symb + save_p);
		*(*s + symb + save_p) = '\0';
		if ((chang = VAR->chop("env", *s + symb + 1)))
			chang = ft_strdup(chang);
		else
			chang = ft_strdup("");
	}
	*(*s + symb + save_p) = save_c;
	copy(s, symb, chang, save_p);
	ret = ft_strlen(chang);
	free(chang);
	return (ret);
}
