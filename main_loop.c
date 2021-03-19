/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 16:27:17 by mrosette          #+#    #+#             */
/*   Updated: 2021/03/19 17:36:09 by mrosette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include <math.h>

void	my_mlx_pixel_put(t_img *img, int x, int y, unsigned int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}


void	ft_line(int i, int drawStart, int drawEnd, unsigned int color, map_cub *vars, t_img *img)
{
	while (drawStart < drawEnd)
	{
		my_mlx_pixel_put(img, i, drawStart, color);
		drawStart++;
	}
}

int				key_press(int keycode, map_cub *sign)
{

	if (keycode == 53) //Quit the program when ESC key pressed
		exit(0);
	// if (keycode == 0)
	// {
	// 	//printf("i am here and my dirX %f\n", sign->dirX);
	// 	if (sign->map_arr[(int)sign->posX][(int)(sign->posY + sign->dirX * 0.25)] == 0)
	// 		sign->posY += sign->dirX * 0.25;
	// 	if (sign->map_arr[(int)(sign->posX - sign->dirY * 0.25)][(int)sign->dirY] == 0)
	// 	 	sign->dirX = 0;
	// }
	if (keycode == W)
	{
		//printf("i am here");
		if(sign->map_arr[(int)(sign->posX + sign->dirX * 0.25)][(int)(sign->posY)] == '0')
				sign->posX += sign->dirX * 0.25;
      	if(sign->map_arr[(int)(sign->posX)][(int)(sign->posY + sign->dirY * 0.25)] == '0')
		  		sign->posY += sign->dirY * 0.25;
	}
	if (keycode == SS)
	{
		//printf("i am here");
		if(sign->map_arr[(int)(sign->posX - sign->dirX * 0.25)][(int)(sign->posY)] == '0')
				sign->posX -= sign->dirX * 0.25;
      	if(sign->map_arr[(int)(sign->posX)][(int)(sign->posY - sign->dirY * 0.25)] == '0')
		  		sign->posY -= sign->dirY * 0.25;
	}
	if (keycode == A)
	{
		//printf("i am here");
		if(sign->map_arr[(int)(sign->posX - sign->dirY * 0.25)][(int)(sign->dirY)] == '0')
				sign->posX -= sign->dirX * 0.25;
      	if(sign->map_arr[(int)(sign->posX)][(int)(sign->posY + sign->dirX * 0.25)] == '0')
		  		sign->posY += sign->dirY * 0.25;
	}
	if (keycode == D)
	{
		//printf("i am here");
		if(sign->map_arr[(int)sign->dirX][(int)(sign->posY + sign->dirX * 0.25)] == '0')
				sign->posY -= sign->dirX * 0.25;
      	if(sign->map_arr[(int)(sign->dirY)][(int)(sign->posX + sign->dirY * 0.25)] == '0')
		  		sign->posX += sign->dirY * 0.25;
	}
	if (keycode == 123)
	{
		double olddir = sign->dirX;
		double oldplanex = sign->planeX;

		sign->dirX = sign->dirX * cos(sign->rotspeed) - sign->dirY * sin(sign->rotspeed);
		sign->dirY = olddir * sin(sign->rotspeed) + sign->dirY * cos(sign->rotspeed);

		sign->planeX = sign->planeX * cos(sign->rotspeed) - sign->planeY * sin(sign->rotspeed);
		sign->planeY = oldplanex * sin(sign->rotspeed) + sign->planeY * cos(sign->rotspeed);
	}
	if (keycode == 124)
	{
		double olddir = sign->dirX;
		double oldplanex = sign->planeX;

		sign->dirX = sign->dirX * cos(-sign->rotspeed) - sign->dirY * sin(-sign->rotspeed);
		sign->dirY = olddir * sin(-sign->rotspeed) + sign->dirY * cos(-sign->rotspeed);

		sign->planeX = sign->planeX * cos(-sign->rotspeed) - sign->planeY * sin(-sign->rotspeed);
		sign->planeY = oldplanex * sin(-sign->rotspeed) + sign->planeY * cos(-sign->rotspeed);
	}
	return (0);
}

int		ft_ray(map_cub *sign)
{
	t_img img;
	int i = 0;

	//printf("\n\n %f \n%f \n\n",sign->posX, sign->posY);
	//printf("my dirx is a %f\n", sign->dirX);
	//printf("\n %f \n %f \n", sign->posX, sign->posY);

	img.img = mlx_new_image(sign->mlx, sign->width, sign->height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

	while (i < sign->width)
	{
		sign->CameraX = 2 * i / (double)sign->width - 1;
		sign->rayDirX = sign->dirX + sign->planeX * sign->CameraX;
		sign->rayDirY = sign->dirY + sign->planeY * sign->CameraX;

	int mapX = (int)sign->posX;
	int mapY = (int)sign->posY;
	double sideDistX;
	double sideDistY;

	double deltaDistX = fabs(1 / sign->rayDirX);
	double deltaDistY = fabs(1 / sign->rayDirY);
	double perpWallDist;
	int stepX;
	int stepY;
	int hit = 0;
	int side = -1;

	if (sign->rayDirX < 0)
	  {
        stepX = -1;
        sideDistX = (sign->posX- mapX) * deltaDistX;
      }
      else
      {
        stepX = 1;
        sideDistX = (mapX + 1.0 - sign->posX) * deltaDistX;
      }
      if (sign->rayDirY < 0)
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
        if (sign->map_arr[mapX][mapY] > '0')
			hit = 1;
      }

	  if (side == 0)
	  	perpWallDist = (mapX - sign->posX + (1 - stepX) / 2) / sign->rayDirX;
      else
	  	perpWallDist = (mapY - sign->posY + (1 - stepY) / 2) / sign->rayDirY;

	  //Calculate height of line to draw on screen
      int lineHeight = (int)(sign->height / perpWallDist);

      //calculate lowest and highest pixel to fill in current stripe
      int drawStart = -lineHeight / 2 + sign->height / 2;
      if(drawStart < 0)
	  	drawStart = 0;
      int drawEnd = lineHeight / 2 + sign->height / 2;
      if(drawEnd >= sign->height)
	  		drawEnd = sign->height - 1;

	 unsigned int color;
			if (sign->posY > mapY && side)
				color = RED;
			else if (sign->posY < mapY && side)
				color = BLUE;
			else if (sign->posX > mapX && !side)
				color = WHITE;
			else if (sign->posX < mapX && !side)
				color = GREEN;

		ft_line(i, drawStart, drawEnd, color, sign, &img);
		i++;

	}
	mlx_put_image_to_window(sign->mlx, sign->win, img.img, 0, 0);
}

void	init_st(map_cub *sign)
{
	sign->dirX = -1;
	sign->dirY = 0;
	sign->planeX = 0;
	sign->planeY = 0.66;
	sign->oldtime = 0;
	sign->time = 0;
	sign->CameraX = 0;
	sign->rayDirX = 0;
	sign->rayDirY = 0;
	sign->rotspeed = 0.05;
}

int		loop_main(map_cub *sign)
{
	init_st(sign);

	sign->mlx = mlx_init();
    sign->win = mlx_new_window(sign->mlx, sign->width, sign->height, "CUB3D");
	mlx_hook(sign->win, 2, 0, &key_press, sign);
	mlx_loop_hook(sign->mlx, ft_ray, sign);
	mlx_loop(sign->mlx);
	return (0);
}
