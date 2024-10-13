# Makefile

NAME = Sokoban

SRCS = main.c \
        plateau.c \
        joueur.c \
        boite.c

all :  $(NAME)

$(NAME): $(SRCS)
	gcc $(SRCS) -o $(NAME)

fclean: 
	rm -f $(NAME)

re: fclean all