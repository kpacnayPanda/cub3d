# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/24 15:14:17 by mrosette          #+#    #+#              #
#    Updated: 2021/02/24 15:17:34 by mrosette         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D.a

LIBFT = libft/libft.a

SRCS = map_parser.c

HEAD = cub.h

OBJS = $(SRCS:.c=.o)

all: libft.a $(NAME)

libft.a:
	$(MAKE) -C libft

$(NAME): $(LIBFT) $(OBJS)
	cp $(LIBFT) $(NAME)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

%.o : %.c $(HEAD)
	#gcc -Wall -Wextra -Werror -I. -Ilibft -c $<
	gcc -I. -Ilibft -c $<

clean:
	$(MAKE) -C libft clean
	rm -rf $(OBJS)

fclean:
	$(MAKE) -C libft fclean
	rm -rf $(OBJS) $(NAME)

re: fclean all

.Phony: all $(NAME) clean fclean re libft.a
