# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hinel-mo <hinel-mo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/03 10:49:28 by hinel-mo          #+#    #+#              #
#    Updated: 2024/12/19 09:44:33 by hinel-mo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME  = get_next_line.a

SRCS =	get_next_line.c \
		get_next_line_utils.c \

OBJS = ${SRCS:.c=.o}

CC = cc

CFLAGS = -Wall -Werror -Wextra -I ./

.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME):$(OBJS)
		ar -rsc $(NAME) $(OBJS)

all:	$(NAME)

clean:	
		rm -f $(OBJS)

fclean:	clean;
		rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re
