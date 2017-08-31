#ifndef PARSER_H
# define PARSER_H

typedef struct		s_exe
{
	char			**arg;
}					t_exe;

typedef struct		s_branche;
{
	t_tree_seg		*new;
	t_list			start;
	t_list			curent;
}					t_branche;
#endif
