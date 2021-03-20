/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 14:36:09 by mrosette          #+#    #+#             */
/*   Updated: 2021/03/20 19:15:08 by mrosette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "libft.h"
# include "minilibx_mms_20200219/mlx.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include "engine.h"
# include <stdio.h> //del

# define WHITE 0x00FFFFFF
# define BLACK 0x00000000
# define RED 0x00FF0000
# define GREEN 0x0000FF00
# define BLUE 0x000000FF
# define MAGENTA 0x00FF00FF
# define YELLOW 0x00FFFF00
# define CYAN 0x0000FFFF

# define BUFFER_SIZE 128

# define W 13
# define SS 1
# define A 0
# define D 2
# define LEFT 123
# define RIGHT 124
# define EXIT 53

typedef struct s_stuct
{
    int width;
    int height;
    char *NO;
    char *SO;
    char *WE;
    char *EA;

    char *S;
    char *F;
    char *C;

    int mapwidth;
    int mapheight;
    int iheight;
    int flag;
    double posX;
    double posY;

    char **map_arr;
	//--------------//

	// void	*mlx;
	// void	*win;
	// double dirX;
	// double dirY;
	// double planeX;
	// double planeY;
	// double time;
	// double oldtime;
	// double CameraX;
	// double rayDirX;
	// double rayDirY;
	// double rotspeed;
	// double movespeed;
}               map_cub;

typedef struct  s_key {
	char		w;
	char		s;
	char		a;
	char		d;
	char		left;
	char		right;
	char		exit;
}				t_key;

typedef struct  s_ray {
	void	*mlx;
	void	*win;
	double dirX;
	double dirY;
	double planeX;
	double planeY;
	double time;
	double oldtime;
	double CameraX;
	double rayDirX;
	double rayDirY;
	double rotspeed;
	double movespeed;
	map_cub sign;
	t_key	key;
}               t_ray;

typedef struct  s_img {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_img;


int		cub_parser(int fd, char **line);
void	find_configs(char *line, map_cub *sign);
void	take_r_specs(char *str, map_cub *sign);
char	*f_strjoin(char *str, char *str2);
char	*copy(char *str, int start, int end);
void	find_path(char *str, map_cub *sign, char id);
void	take_color(char *str, map_cub *sign, char id);
int		check(char *str);
void	check_map(char *str, map_cub *sign);
int		map_error_check(map_cub *sign);
int     trace(map_cub *sign);
void	find_pos(map_cub *sign);
int		loop_main(map_cub *sign);

#endif
