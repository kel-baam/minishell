NAME = minishell
CC = cc
CFLAGS = #-Wall -Wextra -Werror

SUB = main.c utils.c ft_split.c ft_substr.c ft_strdup.c ft_lstadd_back_bonus.c ft_lstnew_bonus.c ft_lstlast_bonus.c ft_strjoin.c ft_strchr.c

OBJ = main.o utils.o ft_split.o ft_substr.o  ft_strdup.o ft_lstadd_back_bonus.o ft_lstnew_bonus.o ft_lstlast_bonus.o ft_strjoin.o ft_strchr.o


all : $(NAME)

$(NAME) :$(SUB)
	${CC} ${CFLAGS} ${SUB}   -o ${NAME}


clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all
