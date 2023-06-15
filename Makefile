NAME = minishell
HOME_BREW_PATH=/Users/kel-baam/goinfre/homebrew
CC = cc

RFLAG = -L ${HOME_BREW_PATH}/opt/readline/lib -I ${HOME_BREW_PATH}/opt/readline/include -lreadline

<<<<<<< HEAD
CFLAGS =#-fsanitize=address -g -Wall -Wextra -Werror
=======
CFLAGS =-fsanitize=address -Wall -Wextra -Werror
>>>>>>> acd60aaddc91b52f518ad0766f860278e8beb2a0

SUB = *.c ./executer/*.c ./parser/*.c ./utils/*.c ./executer/builtins/*.c

OBJ =  *.o ./executer/*.o ./parser/*.o ./utils/*.o ./executer/builtins/*.o


all : $(NAME)

$(NAME) :$(SUB)
	${CC} ${SUB} ${CFLAGS} -o ${NAME} ${RFLAG} -lreadline


clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all
