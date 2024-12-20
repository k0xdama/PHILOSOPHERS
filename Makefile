# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/14 22:33:09 by pmateo            #+#    #+#              #
#    Updated: 2024/11/06 20:28:18 by pmateo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
FLAGS = -Werror -Wextra -Wall -g -g3 -pthread
RM = rm -f
.DEFAULT_GOAL := all

NAME = philo

DIRINC_PHILO = ./INCLUDES
INCFILES = 			${DIRINC_PHILO}/philosophers.h

DIR_SRCS = 			./SRCS/
# SRCS =					main_bis.c routine_bis.c
SRCS = 				main.c ini.c args.c start.c actions.c routine.c checker.c \
					routine_utils.c others_utils.c ft_strcmp.c mutex.c

OBJ = ${SRCS:.c=.o}

%.o: ${DIR_SRCS}%.c ${INCFILES}
	${CC} ${FLAGS} -c $< -o $@ -I ${DIRINC_PHILO}

${NAME}: ${OBJ} ${INCFILES}
	${CC} ${FLAGS} -o ${NAME} ${OBJ} -I ${DIRINC_PHILO}

all: ${NAME}
		@echo "\033[1;5;32m# PHILOSOPHER READY ! #\033[0m"

clean:
		@${RM} ${OBJ} ${OBJ_BONUS}
		@echo "\033[1;9;35m# No more object files. #\033[0m"

fclean: clean
		@${RM} ${NAME} ${NAME_BONUS}
		@echo "\033[1;9;35m# No more executable files. #\033[0m"

re: fclean all

.PHONY: all re clean fclean