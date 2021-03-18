/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 00:34:45 by mrosette          #+#    #+#             */
/*   Updated: 2021/03/17 15:13:31 by mrosette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

typedef struct  s_data {
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
}               t_data;

int				key_press(int keycode, t_data *vars)
{

	if (keycode == 53) //Quit the program when ESC key pressed
		exit(0);
	return (0);
}

void	init_st(t_data *vars)
{
	vars->dirX = -1;
	vars->dirY = 0;
	vars->planeX = 0;
	vars->planeY = 0.66;
	vars->oldtime = 0;
	vars->time = 0;
	vars->CameraX = 0;
	vars->rayDirX = 0;
	vars->rayDirY = 0;
}

int			trace(map_cub *sign)
{
    t_data  vars;
	int i;

	i = 0;

    init_st(&vars);
	vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, 720, 480, "Hello world!");
	mlx_hook(vars.win, 2, 0, &key_press, &vars);
	while (i < sign->width)
	{
		vars.CameraX = (2 * i) / (double)sign->width - 1;
		vars.rayDirX = vars.dirX + (vars.planeX * vars.CameraX);
		vars.rayDirY = vars.dirY + (vars.planeY * vars.CameraX);
		i++;
	}
	int mapX = (int)sign->posX;
	int mapY = (int)sign->posY;
	double sideDistX;
	double sideDistY;

	double deltaDistX = (vars.rayDirY == 0) ? 0 : ((vars.rayDirX == 0) ? 1 : abs(1 / vars.rayDirX));
	double deltaDistY = (vars.rayDirX == 0) ? 0 : ((vars.rayDirY == 0) ? 1 : abs(1 / vars.rayDirY));
	double perpWallDist;
	int stepX;
	int stepY;
	int hit = 0;
	int side;

	if (vars.rayDirX < 0)
      {
        stepX = -1;
        sideDistX = (sign->posX - mapX) * deltaDistX;
      }
      else
      {
        stepX = 1;
        sideDistX = (mapX + 1.0 - sign->posX) * deltaDistX;
      }
      if (vars.rayDirY < 0)
      {
        stepY = -1;
        sideDistY = (sign->posY - mapY) * deltaDistY;
      }
      else
      {
        stepY = 1;
        sideDistY = (mapY + 1.0 - sign->posY) * deltaDistY;
      }

while (hit == 0)
      {
        //jump to next map square, OR in x-direction, OR in y-direction
        if (sideDistX < sideDistY)
        {
          sideDistX += deltaDistX;
          mapX += stepX;
          side = 0;
        }
        else
        {
          sideDistY += deltaDistY;
          mapY += stepY;
          side = 1;
        }
        //Check if ray has hit a wall
        if (sign->map_arr[mapX][mapY] > 0) hit = 1;

		if (hit > 0)
			printf("I hit the wall: %d %d", mapX, mapY);
      }

	  if (side == 0) perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
      else           perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

	  //Calculate height of line to draw on screen
      int lineHeight = (int)(sign->height / perpWallDist);

      //calculate lowest and highest pixel to fill in current stripe
      int drawStart = -lineHeight / 2 + sign->height / 2;
      if(drawStart < 0)drawStart = 0;
      int drawEnd = lineHeight / 2 + sign->height / 2;
      if(drawEnd >= sign->height)drawEnd = sign->height - 1;

    mlx_loop(vars.mlx);
}




