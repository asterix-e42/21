/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_klein.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 02:02:14 by tdumouli          #+#    #+#             */
/*   Updated: 2017/09/28 02:20:32 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "mini.h"
#include <stdlib.h>

char		**str_str_ralloc(int diff, char **str)
{
	char		**new;
	int			lenght;

	lenght = -1;
	if (!str)
		++lenght;
	else
		while (*(str + ++lenght))
			;
	if (!(new = (char **)malloc(sizeof(char *) * (lenght + diff + 1))))
		return (NULL);
	*(new + lenght + diff) = NULL;
	if (str)
		while (--lenght != -1)
			*(new + lenght) = *(str + lenght);
	return (new);
}

int			str_strlen(void **s)
{
	size_t		t;

	t = 0;
	while (*(t + s))
		t++;
	return (t);
}

char		**str_strdup(char *str)
{
	char		**ret;

	ret = (char **)malloc(sizeof(char *) * 2);
	*(ret + 1) = (char *)0;
	*ret = ft_strdup(str);
	return (ret);
}

void		*parse_error(t_token *tok)
{
	VAR->add_bout("hidden", "parse", "!");
	erreur(SHELL, "parse error near `", NULL);
	write(2, tok->start, tok->len);
	write(2, "'\n", 2);
	return (NULL);
}
