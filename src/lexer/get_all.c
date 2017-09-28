/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_all.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 02:41:59 by tdumouli          #+#    #+#             */
/*   Updated: 2017/09/28 02:46:55 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get.h"

int		verrif_all(char *str, t_res_name *parc)
{
	return (str && ((*parc = lexer_get_comment(parc->text)).text != str
				|| (*parc = lexer_get_control(parc->text)).text != str
				|| (*parc = lexer_get_reserv(parc->text)).text != str
				|| (*parc = lexer_get_separator(parc->text)).text != str
				|| (*parc = lexer_get_space(parc->text)).text != str
				|| (*parc = lexer_get_nbr(parc->text)).text != str
				|| (*parc = lexer_get_newline(parc->text)).text != str
				|| (*parc = lexer_get_cote(parc->text)).text != str
				|| (*parc = lexer_get_cont(parc->text)).text != str
		|| (parc->text && (*parc = lexer_get_cmd(parc->text)).text != str)));
}
