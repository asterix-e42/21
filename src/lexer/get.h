/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 02:47:27 by tdumouli          #+#    #+#             */
/*   Updated: 2017/09/28 02:59:00 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_H
# define GET_H

# include "lexer.h"

t_res_name	lexer_get_separator(char *str);
t_res_name	lexer_get_control(char *str);
t_res_name	lexer_get_cmd(char *str);
t_res_name	lexer_get_nbr(char *str);
t_res_name	lexer_get_cont(char *str);
t_res_name	lexer_get_space(char *str);
t_res_name	lexer_get_newline(char *str);
t_res_name	lexer_get_cote(char *str);
t_res_name	lexer_get_comment(char *str);
t_res_name	lexer_get_reserv(char *str);

#endif
