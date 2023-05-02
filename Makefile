NAME = minishell
CC = cc
CFLAGS = -fsanitize=address #-Wall -Wextra -Werror

SUB = *.c ./executer/*.c ./parser/*.c ./utils/*.c

OBJ =  *.o ./executer/*.o ./parser/*.o ./utils/*.o


all : $(NAME)

$(NAME) :$(SUB)
	${CC} ${CFLAGS} -lreadline ${SUB}   -o ${NAME}


clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all
