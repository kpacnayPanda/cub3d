/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 16:27:17 by mrosette          #+#    #+#             */
/*   Updated: 2021/03/18 18:07:31 by mrosette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include <math.h>

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}


void	ft_line(int i, int drawStart, int drawEnd, unsigned int color, t_data *vars, t_img *img)
{
	while (drawStart < drawEnd)
	{
		my_mlx_pixel_put(img, i, drawStart, color);
		drawStart++;
	}
}

int		loop_main(t_data *vars)
{
	t_img img;
	int i = 0;

	img.img = mlx_new_image(vars->mlx, vars->sign.width, vars->sign.height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

	while (i < vars->sign.width)
	{
		vars->CameraX = (2 * i) / (double)vars->sign.width - 1;
		vars->rayDirX = vars->dirX + (vars->planeX * vars->CameraX);
		vars->rayDirY = vars->dirY + (vars->planeY * vars->CameraX);

	int mapX = (int)vars->sign.posX;
	int mapY = (int)vars->sign.posY;
	double sideDistX;
	double sideDistY;

	double deltaDistX = (vars->rayDirY == 0) ? 0 : ((vars->rayDirX == 0) ? 1 : fabs(1 / vars->rayDirX));
	double deltaDistY = (vars->rayDirX == 0) ? 0 : ((vars->rayDirY == 0) ? 1 : fabs(1 / vars->rayDirY));
	double perpWallDist;
	int stepX;
	int stepY;
	int hit = 0;
	int side = -1;

	if (vars->rayDirX < 0)
	  {
        stepX = -1;
        sideDistX = (vars->sign.posX - mapX) * deltaDistX;
      }
      else
      {
        stepX = 1;
        sideDistX = (mapX + 1.0 - vars->sign.posX) * deltaDistX;
      }
      if (vars->rayDirY < 0)
      {
        stepY = -1;
        sideDistY = (vars->sign.posY - mapY) * deltaDistY;
      }
      else
      {
        stepY = 1;
        sideDistY = (mapY + 1.0 - vars->sign.posY) * deltaDistY;
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
        if (vars->sign.map_arr[mapX][mapY] > 0) hit = 1;

		//if (hit > 0)
			//printf("I hit the wall: %d %d", mapX, mapY);
			//exit(0);
      }

	  if (side == 0)
	  	perpWallDist = (mapX - vars->sign.posX + (1 - stepX) / 2) / vars->rayDirX;
      else
	  	perpWallDist = (mapY - vars->sign.posY + (1 - stepY) / 2) / vars->rayDirY;

	  //Calculate height of line to draw on screen
      int lineHeight = (int)(vars->sign.height / perpWallDist);

      //calculate lowest and highest pixel to fill in current stripe
      int drawStart = -lineHeight / 2 + vars->sign.height / 2;
      if(drawStart < 0)drawStart = 0;
      int drawEnd = lineHeight / 2 + vars->sign.height / 2;
      if(drawEnd >= vars->sign.height)drawEnd = vars->sign.height - 1;

	 unsigned int color = 0x0;
			if (vars->sign.posY > mapY && side)
				color = 0x00FF0000;
			else if (vars->sign.posY < mapY && side)
				color = 0x000000FF;
			else if (vars->sign.posX > mapX && !side)
				color = 0x00FFFFFF;
			else if (vars->sign.posX < mapX && !side)
				color = 0x0000FF00;

	  //if (side == 1) {color = color / 2;}

		ft_line(i, drawStart, drawEnd, color, vars, &img);
		i++;
	}

	mlx_put_image_to_window(vars->mlx, vars->win, img.img, 0, 0);
	return (0);
}
