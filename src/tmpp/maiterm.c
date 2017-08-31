
#include <stdio.h>
#include "lexer.h"
#include "g.h"

#include <unistd.h>

int main()
{
	char *s;
	t_lexer     *tex;

	write(1, "$> ", 3);
	s = saisie();
	tex = lexer_init(s);
	lexer(tex);
	if (tex)
	{
		print_lex(*tex);
		ast(*tex);
	}
	//printf("\n%s\n", s);
}
