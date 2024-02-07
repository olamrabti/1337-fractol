# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/30 18:03:20 by olamrabt          #+#    #+#              #
#    Updated: 2024/02/07 18:52:42 by olamrabt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRCS = fractol.c fractol_utils.c ft_atof.c

NAME = fractol

FLAGS = -Wall -Werror -Wextra -lmlx -framework OpenGL -framework AppKit

OBJS = $(SRCS:.c=.o)

RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	cc $(FLAGS) $(OBJS) -o $@

%.o: %.c fractol.h
	cc -Wall -Werror -Wextra -c $<

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: fclean clean  all re 
