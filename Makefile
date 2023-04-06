NAME		= philo
INCLUDE		= -Iincludes
FLAGS		= -Wall -Werror -Wextra -fsanitize=thread -g3
CC			= gcc
RM			= rm -rf
OBJS_DIR	= ./obj

SRCS		= ${wildcard philo_srcs/*.c}

P_OBJS		= ${SRCS:philo_srcs/%.c=${OBJS_DIR}/%.o}

GREEN		= \033[0;92m
RED			= \033[0;91m
RESET		= \033[0m

vpath %.c philo_srcs

all		: ${NAME}

${NAME} : ${P_OBJS}
	@${CC} ${FLAGS} ${INCLUDE} -pthread $^ -o $@
	@echo "${GREEN}Compiling...${RESET}"

obj/%.o : %.c
	@mkdir -p obj
	@${CC} ${FLAGS} ${INCLUDE} -c $< -o $@

clean :
	@rm -rf obj 
	@echo "${RED}Cleaning binary files 'philo_srcs'...${RESET}"
	@echo "${RED}Removing objects directory...${RESET}"

fclean : clean
	@rm -rf ${NAME}

re 		: fclean all

.PHONY	: all clean fclean re