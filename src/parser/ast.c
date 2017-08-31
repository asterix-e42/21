/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 16:09:23 by tdumouli          #+#    #+#             */
/*   Updated: 2017/08/27 20:43:32 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <unistd.h>
#include <stdlib.h>
//char	**realloc_dstr(char **prev, t_token)

/*char **make_cmd(t_lexer lex)
  {
  char **cmd;

  while (((t_token *)tex->token->content)->len
  && ((t_token *)tex->token->content)->type != TK_SEPARATOR)
  {

  }
  }
  */

void	print_ast(t_leaf *start)
{
	int i;

	i = -1;
	(void)start;
/*		ft_putnbr (((t_ast *)start->content)->flag);
		write(1, "[", 1);
		if (((t_ast *)start->content)->flag)
		write(1, ((t_ast *)start->content)->tok->start, ((t_ast *)start->content)->tok->len);
		else
		{
		if (((t_ast *)start->content)->argv)
		while (*(++i + ((t_ast *)start->content)->argv))
		{
		ft_putstr(*(((t_ast *)start->content)->argv + i));
		write(1, "   ", 3);
		}
		if (((t_ast *)start->content)->redir)
		{
		write(1, "{", 1);
		ft_putnbr(((t_redir *)((t_ast *)start->content)->redir->content)->in);
		write(1, ((t_redir *)((t_ast *)start->content)->redir->content)->tok->start,
		((t_redir *)((t_ast *)start->content)->redir->content)->tok->len);
		if (((t_redir *)((t_ast *)start->content)->redir->content)->out < 0)
		ft_putstr(((t_redir *)((t_ast *)start->content)->redir->content)->file);
		else
		ft_putnbr(((t_redir *)((t_ast *)start->content)->redir->content)->out);
		write(1, "}", 1);
		}
		else
		write(1, "{no redir}", 10);
		}
		write(1, "]", 1);*/
}

t_list  *new_redir(t_lexer *lex)
{
	t_redir		ret;

	if ((((t_token *)lex->token->content)->type) == TK_NBR)
	{
		ret.in = ft_atoi(((t_token *)lex->token->content)->start);
		lex->token = lex->token->next;
	}
	else
		ret.in = ('>' == *((t_token *)lex->token->content)->start);
	ret.tok = ((t_token *)lex->token->content);
	//write(1, ret.tok->start, 1);
	lex->token = lex->token->next;
	ret.out = (*(((t_token *)lex->token->content)->start - 1) == '&') ? -1 : -2;
	while (((t_token *)lex->token->content)->type == TK_BLANK)
		lex->token = lex->token->next;
	if (ret.out == -1 && ((t_token *)lex->token->content)->type == TK_NBR)
		ret.out = ft_atoi(((t_token *)lex->token->content)->start);
	else
		ret.file = ft_strndup((((t_token *)lex->token->content)->start),
				(((t_token *)lex->token->content)->len));
	return (ft_lstnew(&ret, sizeof(t_redir)));
}
/*
   t_leaf	*new_redir(int in, int out)
   {
   t_redir	ret;

   ret.in = in;
   ret.out = out;
   return (ft_treenew(&ret, sizeof(t_redir)));
   }*/

int		next_type(t_list *lex, e_token_type type)
{
	t_token *tok;
	while ((tok = (t_token *)lex->next->content) && tok->len && (
				tok->type == TK_BLANK))
		lex = lex->next;
	return (tok->type == type || !tok->len);
}

t_leaf	*new_ast(t_lexer *lex, char flag)
{
	t_ast	ret;
	t_leaf	*leaf;

	while (flag && (((t_token *)lex->token->content)->len) &&
			((t_token *)(lex->token->content))->type == TK_BLANK)
		lex->token = lex->token->next;
	ret.tok = (flag) ? ((t_token *)(lex->token->content)) : (t_token *)lex;
	ret.assign = NULL;
	ret.argv = NULL;
	ret.redir = NULL;
	ret.flag = 0;
	ret.argc = 0;
	if (flag && ((t_token *)(lex->token->content))->type == TK_CONTROL)
	{
		write(1, "parse error2\n", 13);
		return (NULL);
	}
	else if (flag && ((t_token *)(lex->token->content))->type == TK_ACOLAD)
	{
		if (!next_type(lex->token, TK_CONTROL))
			return (NULL);
		else
		{
			leaf = ft_treenew(&ret, sizeof(t_ast));
			leaf->droite = new_secleaf(lex->token->content);
			((t_ast *)(leaf)->content)->flag = 5;
			write(1, "q", 4);
		}
	}
	else
		leaf = ft_treenew(&ret, sizeof(t_ast));
	//write(1, "[", 1);
	//ft_treeiter(leaf, print_ast);
	//write(1, "]", 1);
	return (leaf);
}

int add_control(t_leaf **start, t_leaf **pourquoi, t_token *tok)
{
	t_leaf	*tmp;

	if (!(tmp = new_ast((t_lexer *)tok, 0)))
		return (1);
	if (tok->len == 1 && *tok->start == ';')
		((t_ast *)(tmp)->content)->flag = 9;
	else if (((t_ast *)(*pourquoi)->content)->tok->type == TK_CONTROL)
	{
		//	print_ast(*start);
		((t_ast *)((*start)->content))->flag = 255;
		write(2, "parse error\n", 12);
		ft_treeaddd(*pourquoi, tmp);
		return (1);
	}
	else if (tok->len == 1 && *tok->start == '&')
		((t_ast *)(tmp)->content)->flag = 9;
	else if (tok->len == 2 && (*tok->start == '&' || *tok->start == '|'))
	{
		while((*pourquoi)->prev && ((t_ast *)(*pourquoi)->content)->flag < 9)
			*pourquoi = (*pourquoi)->prev;
		((t_ast *)(tmp)->content)->flag = 8;
	}
	else if (tok->len == 1 && *tok->start == '|')
	{
		while((*pourquoi)->prev && ((t_ast *)(*pourquoi)->content)->flag < 8)
			*pourquoi = (*pourquoi)->prev;
		((t_ast *)(tmp)->content)->flag = 6;
	}
	if ((!(*pourquoi)->prev && ((t_ast *)(tmp)->content)->flag >=
				((t_ast *)(*start)->content)->flag) || ((t_ast *)(tmp)->content)->flag == 9)
	{
		tmp->gauche = *start;
		*start = tmp;
	}
	else
		ft_treeaddd(*pourquoi, tmp);
	*pourquoi = tmp;
	return (0);
}

t_leaf	*new_secleaf(t_token *tok)
{
	//	t_leaf	*start;
	t_lexer	*sec_lex;
	char	*tmp;

	if (tok->len <= 2)
	{
		write(1, "vide\n", 5);
		return (NULL);
	}
	tmp = ft_strsub(tok->start, 1, tok->len - 2);
	sec_lex = lexer_init(tmp);
	free(tmp);
	lexer(sec_lex);
	if (sec_lex)
	{
		//		write(1, "i", 4);
		//print_lex(*sec_lex);
		//ft_treeiter(ast(*sec_lex), print_ast);
		return(ast(*sec_lex));
	}
	//	write(1, "r", 4);
	//start = new_ast(sec_lex, 2);

	//ft_treeaddfromprev(actuel, );
	return (NULL);
}


char        **str_str_ralloc(int diff, char **str)
{
	char    **new;
	int     lenght;

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

int str_strlen(void **s)
{
	size_t  t;

	t = 0;
	while (*(t + s))
		t++;
	return (t);
}

void	set_ast_args(t_token *elem, t_ast *ast)
{
	char	**tmp;
	char	**tmp2;
	char	*str;
	int		flag_cote;

	flag_cote = (elem->type == TK_SCOTE || elem->type == TK_DCOTE);
	if (flag_cote && elem->len == 2)
		return ;
	str = ft_strnew(elem->len - (2 * flag_cote));
	ft_strncat(str, elem->start + flag_cote, elem->len - (2 * flag_cote));
	if (elem->type != TK_SCOTE)
		change(&str, flag_cote, ast->argv);
	tmp2 = ft_strsplit(str, ' ');
	if ((flag_cote = str_strlen((void **)tmp2)))
	{
	//write(1, "\n", 1);
	//ft_putnbr(flag_cote);
	//ft_putstr(str);
	//write(1, "\n", 1);
	tmp = str_str_ralloc(flag_cote, ast->argv);
	while (flag_cote--)
		*(tmp + ast->argc + flag_cote) = *(tmp2 + flag_cote);
	free(ast->argv);
	ast->argv = tmp;
	++ast->argc;
	}
	if (ast->argc == 1)
		ast->cmd = str;
}

t_leaf	*ast(t_lexer lex)
{
	t_leaf	*start;
	t_leaf	*parceque;

	//if (((t_ast *)start->content)->tok->type == TK_CONTROL)
	//	write(1, "1", 1);
	//return (NULL);
	if (!(start = new_ast(&lex, 1)))
		return (NULL);
	parceque = start;
	while (((t_token *)lex.token->content)->len)
	{
		//	write(1, "r		", 3);
		if ((((t_token *)lex.token->content)->type) == TK_CONTROL)
		{
			//		write(1, "C		", 3);
			if (add_control(&start, &parceque, lex.token->content))
			{
				//			write(1, "nop", 3);
				return (start);
			}
			lex.token = lex.token->next;
			if(ft_treeaddd(parceque, new_ast(&lex, 1)))
				return (start);
			parceque = parceque->droite;
		}
		if (((((t_token *)lex.token->content)->type) == TK_NBR &&
					(((t_token *)lex.token->next->content)->type) == TK_REDIR) ||
				(((t_token *)lex.token->content)->type) == TK_REDIR)
		{
			//		write(1, "essai7\n", 7);
			ft_lstadd(&(((t_ast *)parceque->content)->redir), new_redir(&lex));
		}
		else if ((((t_token *)lex.token->content)->type) == TK_ACOLAD)
		{
			//write(2, "parse ok\n", 9);
			//	write(1, "\n", 7);
			//ft_treeaddfromprev(parceque, new_secleaf(lex.token->content, parceque));
		}
		else if ((((t_token *)lex.token->content)->type) == TK_PARENT)
			write(1, "essai3\n", 7);
		else if ((((t_token *)lex.token->content)->type) == TK_ASSEGMT)
			write(1, "essai2\n", 7);
		else if ((((t_token *)lex.token->content)->type) == TK_CMD ||
				(((t_token *)lex.token->content)->type) == TK_NBR ||
				(((t_token *)lex.token->content)->type) == TK_SCOTE ||
				(((t_token *)lex.token->content)->type) == TK_DCOTE)
		{
			//write(1, "essai2\n", 7);
			set_ast_args(lex.token->content, parceque->content);
		}

		//if ((((t_token *)lex.token->content)->type) == TK_CMD)
		if (((t_token *)lex.token->content)->len)
			lex.token = lex.token->next;
		//	ft_treeiter(start, print_ast);
	}
	//	write(1, "i\n", 2);
	ft_treeiter(start, print_ast);
	return (start);
}
