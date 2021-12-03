# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/25 15:08:29 by ldermign          #+#    #+#              #
#    Updated: 2021/12/04 00:36:57 by ldermign         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo

SRCS	=	srcs/main.c \
			srcs/parsing.c \
			srcs/init.c \
			srcs/start_philosophers.c \
			srcs/routine.c \
			srcs/think_eat_sleep.c \
			srcs/checkers.c \
			srcs/free.c \
			srcs/utils_parsing.c \
			srcs/utils_time.c \
			srcs/utils_lock_mutex.c


OBJS	=	${SRCS:.c=.o}

DEPS	=	${SRCS:.c=.d}

INCS	=	./incs/

CC		=	clang

CFLAGS	=	-Wall -Wextra -Werror -DLinux -I ${INCS}

RM		=	rm -rf

all:		${NAME}

${NAME}:	${OBJS}
			@${CC} -lpthread ${CFLAGS} -o $@ $^
# // entre $@ $^ y'a -ggdb3

-include	${DEPS}

.c.o:
			@${CC} -c ${CFLAGS} -o $@ $^
# %.o:%.c
# @${CC} ${CFLAGS} -o $@ -c $<
# @${CC} ${CFLAGS} -MMD -MP -MF ${@:.o=.d} -o $@ -c $<

clean:
			@${RM} ${OBJS} ${DEPS}

fclean:		clean
			@${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re