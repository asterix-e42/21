/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tent.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 17:16:38 by tdumouli          #+#    #+#             */
/*   Updated: 2017/05/17 18:54:30 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TENT_H
# define TENT_H

# include "libft.h"

typedef struct	s_private
{
	char		*name;
	char		*value;
}				t_private;

typedef struct	s_function
{
	t_list		*(*init)(char *);
	void		(*print)(char *, char *);
	void		(*unset)(char *, char *);
	char		*(*chop)(char *, char *);
	char		**(*chop_all)(char *);
	void		(*add)(char *, char **, unsigned int);
	void		(*add_bout)(char *, char *, char *);
}				t_function;

typedef struct	s_the_one_struct
{
	t_function	*fun;
	t_list		*var;
}				t_the_one_struct;

typedef struct	s_var
{
	char		*name;
	t_list		*privat;
}				t_var;

void			destroy(char *nam_var, char *name_priv);
t_function		*all_var(int choix);
t_var			*ft_lstfind_var(char *nam);
t_list			*ft_lstfind_priv(char *nam, t_list *are_you);
void			print(char *nam_var, char *name_priv);
t_list			*init_var(char *nam);
void			add(char *nam, char **ajout, unsigned int nb);
void			add_bout(char *nam, char *name, char *value);
char			*chop(char *nam_var, char *name_priv);
char			**chop_all(char *nam_var);

#endif
