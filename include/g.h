/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g.h                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/01 13:42:34 by tdumouli          #+#    #+#             */
/*   Updated: 2017/09/03 21:39:41 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef G_H
# define G_H

# define MIN(x,y) ((x) < (y) ? (x) : (y))
# define MAX(x,y) ((x) > (y) ? (x) : (y))

typedef struct	s_data {
	char	*str;
	int		len;
	int		pointeur;
	int		pos_start;
}				t_data;

typedef struct	s_fd{
	int fd_stn[2];
	int fd_err[2];
}				t_fd;

void			execmain(char *string);
char			*saisie(void);
void			clean(t_data *blk);
void			yolo(int dir, int y);
t_data			*t_dat_init(void);
void			point(t_data *blk, int fg);
void			set_t_data_pointeur(t_data *blk, int inc);

char			*recule(t_data *blk);
int				ft_alloc(t_data *data, char *ajout);

int				pass_canonique(void);

void			move_simple(char *s, t_data *blk);
void			move_simple_depl(char *s, t_data *blk);

char			*get_hist(int up);
char			*fleme(void);
char			*set_hist(char *stri, char c);
void			cutinhist(char *pas, char *nam);

void			replace(t_data *blk, char *n);
void			ft_write(int fd, char *str, int len);
void			cutpaste(char *c, t_data *b);
void			ajout_str(char *c, t_data *blk);

#endif
