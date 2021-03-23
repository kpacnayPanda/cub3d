/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 16:27:17 by mrosette          #+#    #+#             */
/*   Updated: 2021/03/23 14:26:16 by mrosette         ###   ########.fr       */
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

void		move_player(t_ray *ray)
{
	map_cub *sign;

	sign = &(ray->sign);
	if (ray->key.exit) //Quit the program when ESC key pressed
		exit(0);

	if (ray->key.w)
	{
		if(sign->map_arr[(int)(sign->posX + ray->dirX * ray->movespeed)][(int)(sign->posY)] == '0')
				sign->posX += ray->dirX * ray->movespeed;
      	if(sign->map_arr[(int)(sign->posX)][(int)(sign->posY + ray->dirY * ray->movespeed)] == '0')
		  		sign->posY += ray->dirY * ray->movespeed;
	}
	if (ray->key.s)
	{
		if(sign->map_arr[(int)(sign->posX - ray->dirX * ray->movespeed)][(int)(sign->posY)] == '0')
				sign->posX -= ray->dirX * ray->movespeed;
      	if(sign->map_arr[(int)(sign->posX)][(int)(sign->posY - ray->dirY * ray->movespeed)] == '0')
		  		sign->posY -= ray->dirY * ray->movespeed;
	}
	if (ray->key.a)
	{
		if(sign->map_arr[(int)sign->posX][(int)(sign->posY + ray->dirX * ray->movespeed)] == '0')
			sign->posY += ray->dirX * ray->movespeed;
		if(sign->map_arr[(int)(sign->posX - ray->dirY * ray->movespeed)][(int)sign->posY] == '0')
			sign->posX -= ray->dirY * ray->movespeed;
	}
	if (ray->key.d)
	{
		if(sign->map_arr[(int)sign->posX][(int)(sign->posY - ray->dirX * ray->movespeed)] == '0')
			sign->posY -= ray->dirX * ray->movespeed;
		if(sign->map_arr[(int)(sign->posX + ray->dirY * ray->movespeed)][(int)sign->posY] == '0')
			sign->posX += ray->dirY * ray->movespeed;
	}
	if (ray->key.left)
	{
		double olddir = ray->dirX;
		double oldplanex = ray->planeX;

		ray->dirX = ray->dirX * cos(ray->rotspeed) - ray->dirY * sin(ray->rotspeed);
		ray->dirY = olddir * sin(ray->rotspeed) + ray->dirY * cos(ray->rotspeed);

		ray->planeX = ray->planeX * cos(ray->rotspeed) - ray->planeY * sin(ray->rotspeed);
		ray->planeY = oldplanex * sin(ray->rotspeed) + ray->planeY * cos(ray->rotspeed);
	}
	if (ray->key.right)
	{
		double olddir = ray->dirX;
		double oldplanex = ray->planeX;

		ray->dirX = ray->dirX * cos(-ray->rotspeed) - ray->dirY * sin(-ray->rotspeed);
		ray->dirY = olddir * sin(-ray->rotspeed) + ray->dirY * cos(-ray->rotspeed);

		ray->planeX = ray->planeX * cos(-ray->rotspeed) - ray->planeY * sin(-ray->rotspeed);
		ray->planeY = oldplanex * sin(-ray->rotspeed) + ray->planeY * cos(-ray->rotspeed);
	}
}

//----------------

unsigned int      get_color(t_img *data, int x, int y)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    return (*(unsigned int*)dst);
}

void	ft_line3(int i, int drawStart, int drawEnd, t_img *img, int texX, t_img *wood, int lineHeight, int side, map_cub sign)
{
  unsigned int color;
  double texPos;
  double step = 1.5 * sign.height / lineHeight;
  double drawing;
  drawing = (double)drawStart;
  texPos = (drawStart - sign.height / 2 + lineHeight / 2) * step;
	while (drawStart < drawEnd)
	{
		color = get_color(wood, texX, texPos/17);
    if( color != 0x000000)
      my_mlx_pixel_put(img, i, drawStart, color);
    texPos += step ;
		drawStart ++;
	}
}

void	ft_line2(int i, int drawStart, int drawEnd, t_img *img, int texX, t_img *wood, int lineHeight, int side, map_cub sign)
{
  unsigned int color;
  double texPos;
  double step = 1.5 * sign.height / lineHeight;
  double drawing;
  drawing = (double)drawStart;
  texPos = (drawStart - sign.height / 2 + lineHeight / 2) * step;
	while (drawStart < drawEnd)
	{
		color = get_color(wood, texX, texPos/17);
    if (side == 1) color = (color >> 1) & 8355711;
    my_mlx_pixel_put(img, i, drawStart, color);
    texPos += step ;
		drawStart ++;
	}
}


//--------------
int		ft_ray(t_ray *ray)
{
	t_img img;
	map_cub sign;
	int i = 0;

	int img_width;
	int img_height;

	sign = ray->sign;
	move_player(ray);

	//text load

	t_img tex1;
	t_img tex2;
	t_img tex3;
	t_img tex4;
	t_img sp;

	tex1.img = mlx_xpm_file_to_image(ray->mlx, "pics/stone.xpm", &img_width, &img_height);
	tex1.addr = mlx_get_data_addr(tex1.img, &tex1.bits_per_pixel, &tex1.line_length, &tex1.endian);
	tex2.img = mlx_xpm_file_to_image(ray->mlx, "pics/brick.xpm", &img_width, &img_height);
	tex2.addr = mlx_get_data_addr(tex2.img, &tex2.bits_per_pixel, &tex2.line_length, &tex2.endian);
	tex3.img = mlx_xpm_file_to_image(ray->mlx, "pics/criper.xpm", &img_width, &img_height);
	tex3.addr = mlx_get_data_addr(tex3.img, &tex3.bits_per_pixel, &tex3.line_length, &tex3.endian);
	tex4.img = mlx_xpm_file_to_image(ray->mlx, "pics/rikardo.xpm", &img_width, &img_height);
	tex4.addr = mlx_get_data_addr(tex4.img, &tex4.bits_per_pixel, &tex4.line_length, &tex4.endian);
	sp.img = mlx_xpm_file_to_image(ray->mlx, "pics/barrel.xpm", &img_width, &img_height);
	sp.addr = mlx_get_data_addr(sp.img, &sp.bits_per_pixel, &sp.line_length, &sp.endian);

	//

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

	// 	//tex rend

		double wallX;
            if (side == 0) wallX = sign.posY + perpWallDist * ray->rayDirY;
      else           wallX = sign.posX + perpWallDist * ray->rayDirX;
      wallX -= floor((wallX));
      int texWidth = 64;
      int texX = (int)(wallX * (double)(texWidth));
      if(side == 0 && ray->rayDirX > 0)
	  		texX = texWidth - texX - 1;
      if(side == 1 && ray->rayDirY < 0)
	  		texX = texWidth - texX - 1;

		//

		unsigned int color;
		if (sign.map_arr[mapX][mapY] == '2')
		{

		}
			else if (sign.posY > mapY && side && sign.map_arr[mapX][mapY] != '2')
			{
				ft_line2(i, drawStart, drawEnd, &img, texX, &tex1, lineHeight, side, sign);
			}
			else if (sign.posY < mapY && side && sign.map_arr[mapX][mapY] != '2')
			{
				//color = BLUE;
				ft_line2(i, drawStart, drawEnd, &img, texX, &tex2, lineHeight, side, sign);
				//ft_line(i, drawStart, drawEnd, color, &img);
			}
			else if (sign.posX > mapX && !side && sign.map_arr[mapX][mapY] != '2')
			{
				//color = WHITE;
				ft_line2(i, drawStart, drawEnd, &img, texX, &tex3, lineHeight, side, sign);
				//ft_line(i, drawStart, drawEnd, color, &img);
			}
			else if (sign.posX < mapX && !side && sign.map_arr[mapX][mapY] != '2')
			{
				//color = GREEN;
				ft_line2(i, drawStart, drawEnd, &img, texX, &tex4, lineHeight, side, sign);
				//ft_line(i, drawStart, drawEnd, color, &img);
			}

		int zz;

		zz = 0;
		while (zz < drawStart)
		{
			my_mlx_pixel_put(&img, i, zz, RED);
			zz++;
		}
		zz = drawEnd;
		while (zz < sign.height)
		{
			my_mlx_pixel_put(&img, i, zz, BLUE);
			zz++;
		}

		i++;

	}
	mlx_put_image_to_window(ray->mlx, ray->win, img.img, 0, 0);
}

void	init_st(t_ray *ray, map_cub *sign, t_key key)
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
	ray->rotspeed = 0.02;
	ray->movespeed = 0.1;
	ray->sign = *sign;
	ray->key = key;
}

int		finish(t_ray *ray)
{
	mlx_destroy_window(ray->mlx, ray->win);
	exit (0);
	return (0);
}

int key_pressed(int keycode, t_ray *ray)
{
	if (keycode == W)
		ray->key.w = 1;
	if (keycode == SS)
		ray->key.s = 1;
	if (keycode == A)
		ray->key.a = 1;
	if (keycode == D)
		ray->key.d = 1;
	if (keycode == LEFT)
		ray->key.left = 1;
	if (keycode == RIGHT)
		ray->key.right = 1;
	if (keycode == EXIT)
		ray->key.exit = 1;
}

int key_unpressed(int keycode, t_ray *ray)
{
	if (keycode == W)
		ray->key.w = 0;
	if (keycode == SS)
		ray->key.s = 0;
	if (keycode == A)
		ray->key.a = 0;
	if (keycode == D)
		ray->key.d = 0;
	if (keycode == LEFT)
		ray->key.left = 0;
	if (keycode == RIGHT)
		ray->key.right = 0;
}

int		loop_main(map_cub *sign)
{
	t_ray ray;
	t_key key;
	init_st(&ray, sign, key);

	ray.mlx = mlx_init();
    ray.win = mlx_new_window(ray.mlx, sign->width, sign->height, "CUB3D");
	mlx_hook(ray.win, 2, 0, &key_pressed, &ray);
	mlx_hook(ray.win, 17, 0, finish, &ray);
	mlx_hook(ray.win, 3, 0, &key_unpressed, &ray);
	mlx_loop_hook(ray.mlx, ft_ray, &ray);


	mlx_loop(ray.mlx);
	return (0);
}
