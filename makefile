# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/08 16:51:40 by tdumouli          #+#    #+#              #
#    Updated: 2017/09/28 03:41:37 by tdumouli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SPEUDO = "tdumouli"
NAMEI =
NAME = minishell
OBJDIR = ./objet
SRCDIR = ./src
INCDIR = -I./include -I./libft/include



MINI =	enviede.o is_dir.o utilitaire.o	change.o fenster.o redir.o del.o

EXEC = grsa.o built.o file.o process.o redirec.o

BUILD =	echo.o cd.o exit.o setenv.o

VAR  =	ajout.o detroy.o get.o print.o variable.o

LAXT = lexer/lexer.o lexer/reserv.o lexer/get_1.o lexer/get_2.o lexer/get_all.o\
parser/ast.o parser/ft_klein.o parser/new.o parser/set.o

SAISIE = canonique.o move.o saisie.o t_data_init.o terminal_deplacement.o \
		 utils.o hist.o replace.o

LIB = libft/libft.a

OBJ =	$(addprefix $(OBJDIR)/, $(MINI)) \
		$(addprefix $(OBJDIR)/built/, $(BUILD)) \
		$(addprefix $(OBJDIR)/variable/, $(VAR)) \
		$(addprefix $(OBJDIR)/exec/, $(EXEC)) \
		$(addprefix $(OBJDIR)/, $(LAXT)) \
		$(addprefix $(OBJDIR)/saisie/, $(SAISIE))

LSTDIRI = built variable lexer parser saisie exec
debugg = 

############################## normaly no change ###############################

NO_COLOR="\x1b[39m"
RED="\x1b[31m"
GREEN="\x1b[32m"
YELLOW="\x1b[33m"
CC = gcc
CFLAGS = $(INCDIR) -Wall -Wextra -Werror
DEBU = -fsanitize=address -g3
MAKE = /usr/bin/make

LSTDIR=	$(addprefix $(OBJDIR)/, $(LSTDIRI)) \

ifneq ($(NAMEI), )
all: objdir $(NAMEI)
	@echo $(GREEN)"compilation reussi"$(NO_COLOR)
else
all: objdir $(NAME)
	@echo $(GREEN)"compilation reussi cpl"$(NO_COLOR)
endif

objdir:
	@if ! [ -d $(OBJDIR) ]; then\
		mkdir $(OBJDIR) $(LSTDIR);\
	fi

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@
	@echo $(GREEN)$@" compile"$(NO_COLOR)

$(NAMEI): $(OBJ)
	@ar cr $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo $(GREEN)"library compile"$(NO_COLOR)

$(NAME): $(OBJ)
	$(MAKE) -C ./libft
	$(CC) $(OBJ) ./$(LIB) -o $(NAME) $(DEBUG)
	@echo $(GREEN)$(NAME)" a ete cree"$(NO_COLOR)

clean:
	@$(MAKE) clean -C ./libft
	@rm -rf $(OBJ)
	@$(MAKE) cleanv

ifeq ($(shell find . -type f | grep "\.o"), )
cleanv:
	@echo $(GREEN)"les objets sont clean"$(NO_COLOR)
else
cleanv:
	@echo $(RED)"il ya probleme"
	@echo $(YELLOW)$(shell echo | find . -type f | grep "\.o" | cat -e)
	exit
endif

cl:
	@if [ "test" = "test" ]; then\
		echo "Hello world";\
	fi

auteur:
	@echo $(SPEUDO) > auteur
	@echo $(GREEN)"le fichier auteur a bien ete cree"$(NO_COLOR)

fclean: clean
	@$(MAKE) fclean -C ./libft
	@rm -f $(NAME) $(NAMELIB)
	@echo $(GREEN)"tout est clean"$(NO_COLOR)

re: fclean all

.PHONY: all clean fclean re cleanv anc
