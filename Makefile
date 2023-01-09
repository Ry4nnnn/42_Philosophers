NAME		= philo
INCLUDE		= -Iincludes
FLAGS		= -Wall -Werror -Wextra -fsanitize=thread -g3
CC			= gcc
RM			= rm -rf
OBJS_DIR	= ./obj

SRCS		= ${wildcard philo_srcs/*.c}

P_OBJS		= ${SRCS:philo_srcs/%.c=${OBJS_DIR}/%.o}

vpath %.c philo_srcs

all		: ${NAME}

${NAME} : ${P_OBJS}
	@${CC} ${FLAGS} ${INCLUDE} -pthread $^ -o $@
	@echo "Compiling..."

obj/%.o : %.c
	@mkdir -p obj
	@${CC} ${FLAGS} ${INCLUDE} -c $< -o $@

clean :
	@rm -rf obj 
	@echo "Cleaning binary files 'philo_srcs'..."
	@echo "Removing objects directory..."

fclean : clean
	@rm -rf ${NAME} ${CHECKER}

re 		: fclean all

.PHONY	: all clean fclean re