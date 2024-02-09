# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/30 18:03:20 by olamrabt          #+#    #+#              #
#    Updated: 2024/02/09 16:29:10 by olamrabt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRCS = fractol.c fractol_utils.c fractol_parse.c

SRCS_bonus = fractol_bonus.c fractol_utils_bonus.c fractol_parse_bonus.c do_the_math_bonus.c

NAME = fractol

NAME_bonus = fractol_bonus

FLAGS = -Wall -Werror -Wextra -lmlx -framework OpenGL -framework AppKit

OBJS = $(SRCS:.c=.o)

OBJS_bonus = $(SRCS_bonus:.c=.o)

RM = rm -f

all: $(NAME)

bonus: $(NAME_bonus)

$(NAME): $(OBJS) fractol.h
	cc $(FLAGS) -g $(OBJS) -o $@

$(NAME_bonus): $(OBJS_bonus) fractol_bonus.h
	cc $(FLAGS) -g $(OBJS_bonus) -o $@

%.o: %.c 
	cc -Wall -Werror  -Wextra -c $<

clean:
	$(RM) $(OBJS)

clean_bonus:
	$(RM) $(OBJS_bonus)

fclean: clean
	$(RM) $(NAME)

fclean_bonus: clean_bonus
	$(RM) $(NAME_bonus)

re: fclean all

re_bonus: fclean_bonus bonus

.PHONY: fclean clean  all re re_bonus bonus clean_bonus fclean_bonus
