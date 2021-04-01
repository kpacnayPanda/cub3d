# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/24 15:14:17 by mrosette          #+#    #+#              #
#    Updated: 2021/04/01 17:53:36 by mrosette         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

LIBFT = libft/libft.a

MLX = libmlx.dylib

SRCS = 	src/id_parsing.c \
		src/map_utils.c \
		src/map_errors.c \
		src/path_utils.c \
		src/r_utils.c \
		$(MAIN) \
		src/main_loop.c \
		src/aditional_utils.c \
		src/parse_color.c \
		src/gnl.c \
		src/inits.c \
		src/textures.c \
		src/move_player.c \
		src/move_player2.c \
		src/ray_utils.c \

#**********************MAIN************************#
MAIN_DIR = src/
MAIN = $(MAIN_DIR)main.c
#**************************************************#

#**********************HDRS************************#
INCLD = includes/
HDRS = $(INCLD)cub.h
#**************************************************#

MLXFLAG = -lmlx -framework OpenGL -framework AppKit

MLXDIR = -Iminilibx_mms_20200219

MLX2 = -Lminilibx_mms_20200219


OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(MLX) $(OBJS)
	$(MAKE) -C libft bonus
	$(MAKE) -C minilibx_mms_20200219
	gcc -o $(NAME) $(OBJS) -L libft -lft $(MLX2) $(MLXFLAG)

%.o : %.c $(HEAD)
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
