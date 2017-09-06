/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/26 17:31:39 by tdumouli          #+#    #+#             */
/*   Updated: 2017/09/06 01:42:13 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "libft.h"

typedef enum	e_token_type
{
	TK_NEWLINE,
	TK_BLANK,
	TK_COMMENT,
	TK_CONTROL,
	TK_CMD,
	TK_ASSEGMT,
	TK_NBR,
	TK_SCOTE,
	TK_DCOTE,
	TK_PARENT,
	TK_CROCHET,
	TK_ACOLAD,
	TK_REDIR,
	TK_PLUSTARD,
	TK_IF,
	TK_THEN,
	TK_ELSE,
	TK_ELIF,
	TK_FI,
	TK_CASE,
	TK_IN,
	TK_ESAC,
	TK_FOR,
	TK_WHILE,
	TK_UNTIL,
	TK_DO,
	TK_DONE,
	TK_END
}				t_token_type;

typedef struct	s_token
{
	t_token_type		type;
	char				*start;
	int					len;
}				t_token;

typedef struct	s_res_name
{
	char				*text;
	t_token_type		type;
}				t_res_name;

typedef struct	s_lexer
{
	char				*input;
	t_list				*token;
}				t_lexer;

typedef struct	s_redir
{
	int					in;
	int					out;
	int					fd;
	char				*file;
	t_token				*tok;
}				t_redir;

typedef struct	s_ast
{
	char				**assign;
	t_token				*tok;
	char				**argv;
	int					argc;
	t_list				*redir;
	int					flag;
}				t_ast;

void			set_token_len(t_list *tok, t_res_name re);
t_list			*new_token(char *str);
void			rm_token(void *tok, size_t rien);
int				verrif_all(char *str, t_res_name *parc);

t_leaf			*ast(t_lexer ge);
t_leaf			*new_secleaf(t_token *tok);
void			print_lex(t_lexer tex);
void			lexer(t_lexer *tex);
t_lexer			*lexer_init(char *str);
void			change(char **s, int flagcote, char **sdg);

t_list			*get_resv(void);

#endif
