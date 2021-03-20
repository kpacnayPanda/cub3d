# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/24 15:14:17 by mrosette          #+#    #+#              #
#    Updated: 2021/03/20 17:06:04 by mrosette         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

LIBFT = libft/libft.a

MLX = libmlx.dylib

SRCS = 	src/parse/id_parsing.c \
		src/parse/map_utils.c \
		src/parse/map_errors.c \
		src/parse/path_utils.c \
		src/parse/r_utils.c \
		$(MAIN) \
		src/raycasting/main_loop.c \
		src/aditional_utils.c \
		src/trace.c \

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
