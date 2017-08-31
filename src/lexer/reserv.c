
#include "lexer.h"
#include "libft.h"

static t_list   *new_private(char *name, e_token_type type)
{
	t_res_name   ret;

	ret.text = ft_strdup(name);
	ret.type = type;
	return (ft_lstnew(&ret, sizeof(t_res_name)));
}

static t_list *init(void)
{
	t_list *ret;

	ret = NULL;
	ft_lstadd(&ret, new_private("if", TK_IF));
	ft_lstadd(&ret, new_private("then", TK_THEN));
	ft_lstadd(&ret, new_private("else", TK_ELSE));
	ft_lstadd(&ret, new_private("elif", TK_ELIF));
	ft_lstadd(&ret, new_private("fi", TK_FI));
	ft_lstadd(&ret, new_private("case", TK_CASE));
	ft_lstadd(&ret, new_private("in", TK_IN));
	ft_lstadd(&ret, new_private("esac", TK_ESAC));
	ft_lstadd(&ret, new_private("for", TK_FOR));
	ft_lstadd(&ret, new_private("while", TK_WHILE));
	ft_lstadd(&ret, new_private("until", TK_UNTIL));
	ft_lstadd(&ret, new_private("do", TK_DO));
	ft_lstadd(&ret, new_private("done", TK_DONE));
	return (ret);
}

t_list *get_resv(void)
{
	static t_list *ret = NULL;

	if (!ret)
		ret = init();
	return(ret);
}
