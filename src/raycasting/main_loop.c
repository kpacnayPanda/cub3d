/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 16:27:17 by mrosette          #+#    #+#             */
/*   Updated: 2021/03/20 17:11:03 by mrosette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub.h"
#include <math.h>

void	my_mlx_pixel_put(t_img *img, int x, int y, unsigned int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}


void	ft_line(int i, int drawStart, int drawEnd, unsigned int color, t_img *img)
{
	while (drawStart < drawEnd)
	{
		my_mlx_pixel_put(img, i, drawStart, color);
		drawStart++;
	}
}

int				key_press(int keycode, t_ray *ray)
{
	map_cub *sign;

	sign = &(ray->sign);
	if (keycode == 53) //Quit the program when ESC key pressed
		exit(0);

	if (keycode == W)
	{
		if(sign->map_arr[(int)(sign->posX + ray->dirX * 0.25)][(int)(sign->posY)] == '0')
				sign->posX += ray->dirX * 0.25;
      	if(sign->map_arr[(int)(sign->posX)][(int)(sign->posY + ray->dirY * 0.25)] == '0')
		  		sign->posY += ray->dirY * 0.25;
	}
	if (keycode == SS)
	{
		if(sign->map_arr[(int)(sign->posX - ray->dirX * 0.25)][(int)(sign->posY)] == '0')
				sign->posX -= ray->dirX * 0.25;
      	if(sign->map_arr[(int)(sign->posX)][(int)(sign->posY - ray->dirY * 0.25)] == '0')
		  		sign->posY -= ray->dirY * 0.25;
	}
	if (keycode == A)
	{
		if(sign->map_arr[(int)sign->posX][(int)(sign->posY + ray->dirX * ray->movespeed)] == '0')
			sign->posY += ray->dirX * ray->movespeed;
		if(sign->map_arr[(int)(sign->posX - ray->dirY * ray->movespeed)][(int)sign->posY] == '0')
			sign->posX -= ray->dirY * ray->movespeed;
	}
	if (keycode == D)
	{
		if(sign->map_arr[(int)sign->posX][(int)(sign->posY - ray->dirX * ray->movespeed)] == '0')
			sign->posY -= ray->dirX * ray->movespeed;
		if(sign->map_arr[(int)(sign->posX + ray->dirY * ray->movespeed)][(int)sign->posY] == '0')
			sign->posX += ray->dirY * ray->movespeed;
	}
	if (keycode == 123)
	{
		double olddir = ray->dirX;
		double oldplanex = ray->planeX;

		ray->dirX = ray->dirX * cos(ray->rotspeed) - ray->dirY * sin(ray->rotspeed);
		ray->dirY = olddir * sin(ray->rotspeed) + ray->dirY * cos(ray->rotspeed);

		ray->planeX = ray->planeX * cos(ray->rotspeed) - ray->planeY * sin(ray->rotspeed);
		ray->planeY = oldplanex * sin(ray->rotspeed) + ray->planeY * cos(ray->rotspeed);
	}
	if (keycode == 124)
	{
		double olddir = ray->dirX;
		double oldplanex = ray->planeX;

		ray->dirX = ray->dirX * cos(-ray->rotspeed) - ray->dirY * sin(-ray->rotspeed);
		ray->dirY = olddir * sin(-ray->rotspeed) + ray->dirY * cos(-ray->rotspeed);

		ray->planeX = ray->planeX * cos(-ray->rotspeed) - ray->planeY * sin(-ray->rotspeed);
		ray->planeY = oldplanex * sin(-ray->rotspeed) + ray->planeY * cos(-ray->rotspeed);
	}
	return (0);
}

int		ft_ray(t_ray *ray)
{
	t_img img;
	map_cub sign;
	int i = 0;

	sign = ray->sign;



	img.img = mlx_new_image(ray->mlx, sign.width, sign.height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

	while (i < sign.width)
	{
		ray->CameraX = 2 * i / (double)sign.width - 1;
		ray->rayDirX = ray->dirX + ray->planeX * ray->CameraX;
		ray->rayDirY = ray->dirY + ray->planeY * ray->CameraX;

	int mapX = (int)sign.posX;
	int mapY = (int)sign.posY;
	double sideDistX;
	double sideDistY;

	double deltaDistX = fabs(1 / ray->rayDirX);
	double deltaDistY = fabs(1 / ray->rayDirY);
	double perpWallDist;
	int stepX;
	int stepY;
	int hit = 0;
	int side = -1;

	if (ray->rayDirX < 0)
	  {
        stepX = -1;
        sideDistX = (sign.posX- mapX) * deltaDistX;
      }
      else
      {
        stepX = 1;
        sideDistX = (mapX + 1.0 - sign.posX) * deltaDistX;
      }
      if (ray->rayDirY < 0)
      {
        stepY = -1;
        sideDistY = (sign.posY - mapY) * deltaDistY;
      }
      else
      {
        stepY = 1;
        sideDistY = (mapY + 1.0 - sign.posY) * deltaDistY;
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
        if (sign.map_arr[mapX][mapY] > '0')
			hit = 1;
      }

	  if (side == 0)
	  	perpWallDist = (mapX - sign.posX + (1 - stepX) / 2) / ray->rayDirX;
      else
	  	perpWallDist = (mapY - sign.posY + (1 - stepY) / 2) / ray->rayDirY;

	  //Calculate height of line to draw on screen
      int lineHeight = (int)(sign.height / perpWallDist);

      //calculate lowest and highest pixel to fill in current stripe
      int drawStart = -lineHeight / 2 + sign.height / 2;
      if(drawStart < 0)
	  	drawStart = 0;
      int drawEnd = lineHeight / 2 + sign.height / 2;
      if(drawEnd >= sign.height)
	  		drawEnd = sign.height - 1;

	 unsigned int color;
			if (sign.posY > mapY && side)
				color = RED;
			else if (sign.posY < mapY && side)
				color = BLUE;
			else if (sign.posX > mapX && !side)
				color = WHITE;
			else if (sign.posX < mapX && !side)
				color = GREEN;

		ft_line(i, drawStart, drawEnd, color, &img);
		i++;

	}
	mlx_put_image_to_window(ray->mlx, ray->win, img.img, 0, 0);
}

void	init_st(t_ray *ray, map_cub *sign)
{
	ray->dirX = -1;
	ray->dirY = 0;
	ray->planeX = 0;
	ray->planeY = 0.66;
	ray->oldtime = 0;
	ray->time = 0;
	ray->CameraX = 0;
	ray->rayDirX = 0;
	ray->rayDirY = 0;
	ray->rotspeed = 0.05;
	ray->movespeed = 0.015;
	ray->sign = *sign;
}

int		loop_main(map_cub *sign)
{
	t_ray ray;
	init_st(&ray, sign);

	ray.mlx = mlx_init();
    ray.win = mlx_new_window(ray.mlx, sign->width, sign->height, "CUB3D");
	mlx_hook(ray.win, 2, 0, &key_press, &ray);
	mlx_loop_hook(ray.mlx, ft_ray, &ray);
	mlx_loop(ray.mlx);
	return (0);
}
