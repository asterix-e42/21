/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 00:31:19 by tdumouli          #+#    #+#             */
/*   Updated: 2017/09/24 02:06:48 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include "tent.h"
# include "lexer.h"

# define SHELL "miniii"
# define VAR all_var(0)

typedef struct	s_data {
	char		*str;
	int			len;
	int			pointeur;
}				t_data;
/*
** termcaps
*/
char			*saisie(char *aff, int contrd);
void			clean(t_data *blk);
void			yolo(int dir, int y);
t_data			*t_dat_init(void);
/*
** main
*/
void			sheel(char **av);
int				exe(char *av);
int				execution(t_leaf *branche, int *redir, int pipe);
/*
** environement
*/
void			lvlup(char *env, char *lvl);
/*
** redirection
*/
void			pass(int fd_read, int fd_write);
void			redirpass(t_list *elem);
void			d_redir_g(t_redir *redir, char *av);
int				*fume_pipe(void);
/*
** utils
*/
int				copy(char **s, int symb, char *insert, int save_p);
int				insert_home(char **s, int r);
int				variable(char **s, int symb);
int				echapement(char **s, int symb);
int				is_dir(char *s);
int				new_process(t_ast *ast, char *error, int *flag);

char			*ft_strjoini(char const *s1, char const *s2, char c);
void			freeteuse(void **s, int niveau);
void			whereareyou(char *name);
int				supersplit(char ****ret, char *av, char s1, char s2);
void			erreur(char *a, char *s, char *d);
/*
** built in
*/

/*
** cd.h
*/
void			pwd_short(char **pwd);
void			cd(char *av);
void			built_cd(char **av);

void			ft_setenv(t_ast *ast);

void			ft_echo(char **av);

void			ft_mini_exit(char **av);
#endif
