/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 00:31:19 by tdumouli          #+#    #+#             */
/*   Updated: 2017/09/28 03:54:05 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H

# include <fcntl.h>
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
** del
*/
void			del_t_redir(void *redir, size_t tamere);
void			del_t_ast(void *ast, size_t tamere);
void			del_t_token(void *tok, size_t tamere);
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
int				new_process(t_ast *ast, char *error, int *flag);
int				exe_path(char **av, t_ast *ast, int *flag);
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
int				redi_gauche(t_redir *redi, void *flag_av);
int				redi_droite(t_redir *redi);
/*
** file
*/
void			close_file(t_list *redir_start);
void			close_free(int **fd);
int				open_file(t_list *redir_start, void *flag_av);
void			create_file(t_list *redir_start);
/*
** utils
*/
void			set_hist(char *str);
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

int				built_in_before_fork(t_ast *ast);
int				built_in(t_ast *ast);

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
