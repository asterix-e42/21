/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 03:15:28 by tdumouli          #+#    #+#             */
/*   Updated: 2017/09/28 03:49:18 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mini.h"

int		built_in_before_fork(t_ast *ast)
{
	char	**av;
	int		ret;

	if (!(av = ast->argv) || !*av)
		return (1);
	ret = 0;
	if (ast->argv && !ft_strcmp(*(ast->argv), "exit"))
		ft_mini_exit(ast->argv);
	if (VAR->chop(*av, 0))
		VAR->print(*av, NULL);
	else if (!ft_strcmp(*av, "cd"))
		built_cd(av);
	else if (!ft_strncmp(*av, "set", 3))
		ft_setenv(ast);
	else if (!ft_strncmp(*av, "unset", 5) && ft_strncmp(*av + 5, "hidden", 6))
		while (*(++av))
			VAR->unset(*ast->argv + 5, *av);
	else
		ret = 1;
	return (ret);
}

int		built_in(t_ast *ast)
{
	char	**av;

	if (!(av = ast->argv) || !*av)
		return (1);
	else if (!ft_strcmp(*av, "echo"))
		ft_echo(av);
	else
		return (0);
	return (1);
}
