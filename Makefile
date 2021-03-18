# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/24 15:14:17 by mrosette          #+#    #+#              #
#    Updated: 2021/03/05 01:43:40 by mrosette         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

LIBFT = libft/libft.a

MLX = libmlx.dylib

SRCS = 	cub_parser.c \
		aditional_utils.c \
		id_parsing.c \
		r_utils.c \
		path_utils.c \
		map_utils.c \
		map_errors.c \
		trace.c

MLXFLAG = -lmlx -framework OpenGL -framework AppKit

MLXDIR = -Iminilibx_mms_20200219

MLX2 = -Lminilibx_mms_20200219

#MLX3 = -lmlx

OBJS = $(SRCS:.c=.o)

#all: libft.a libmlx.dylib $(NAME)
all: $(NAME)

#libft.a:
	#$(MAKE) -C libft

#libmlx.dylib:
	#$(MAKE) -C minilibx_mms_20200219

$(NAME): $(MLX) $(OBJS)
	$(MAKE) -C libft bonus
	$(MAKE) -C minilibx_mms_20200219
	gcc -o $(NAME) $(OBJS) -L libft -lft $(MLX2) $(MLXFLAG)
	#$(MLX)
	#gcc $(OBJS) $(MLXFLAG) $(MLXDIR) $(LIBFT) $(MLX) -o $(NAME)
	#gcc $(OBJS) $(MLXFLAG) $(LIBFT) -o $(NAME)

%.o : %.c $(HEAD)
	#gcc -Wall -Wextra -Werror -I. -Ilibft -c $<
	gcc -Wall $(MLXDIR) -I. -Ilibft -c $< -o $@

$(MLX):
	@$(MAKE) -C minilibx_mms_20200219
	@mv minilibx_mms_20200219/$(MLX) .

clean:
	$(MAKE) -C libft clean
	$(MAKE) -C minilibx_mms_20200219 clean
	rm -rf libmlx.dylib
	rm -rf $(OBJS)

fclean:
	$(MAKE) -C libft fclean
	$(MAKE) -C minilibx_mms_20200219 clean
	rm -rf libmlx.dylib
	rm -rf $(OBJS) $(NAME)

re: fclean all

.Phony: all $(NAME) clean fclean re libft.a
