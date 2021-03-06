/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 17:55:32 by tdumouli          #+#    #+#             */
/*   Updated: 2017/03/18 12:58:49 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_strcmp(unsigned char *s1, unsigned char *s2)
{
	int		i;

	i = 0;
	while (*(s1 + i) == *(s2 + i) && *(s2 + i) != '\0')
		i++;
	return (*(s1 + i) - *(s2 + i));
}
