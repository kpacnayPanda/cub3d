/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 16:27:17 by mrosette          #+#    #+#             */
/*   Updated: 2021/04/01 19:24:28 by mrosette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub.h"

void	init_ray(t_trace *trace, t_ray *ray, map_cub sign)
{
	trace->deltaDistX = fabs(1 / ray->rayDirX);
	trace->deltaDistY = fabs(1 / ray->rayDirY);
	trace->hit = 0;
	trace->side = -1;
	if (ray->rayDirX < 0)
	{
		trace->stepX = -1;
		trace->sideDistX = (sign.posX - trace->mapX) * trace->deltaDistX;
	}
	else
	{
		trace->stepX = 1;
		trace->sideDistX = (trace->mapX + 1.0 - sign.posX) * trace->deltaDistX;
	}
	if (ray->rayDirY < 0)
	{
		trace->stepY = -1;
		trace->sideDistY = (sign.posY - trace->mapY) * trace->deltaDistY;
	}
	else
	{
		trace->stepY = 1;
		trace->sideDistY = (trace->mapY + 1.0 - sign.posY) * trace->deltaDistY;
	}
}

void	ray_shoot(t_trace *trace, map_cub sign, t_ray *ray)
{
	while (trace->hit == 0)
	{
		if (trace->sideDistX < trace->sideDistY)
		{
			trace->sideDistX += trace->deltaDistX;
			trace->mapX += trace->stepX;
			trace->side = 0;
		}
		else
		{
			trace->sideDistY += trace->deltaDistY;
			trace->mapY += trace->stepY;
			trace->side = 1;
		}
		if (sign.map_arr[trace->mapX][trace->mapY] == '1')
			trace->hit = 1;
	}
	if (trace->side == 0)
		trace->perpWallDist = (trace->mapX - sign.posX + (1 - trace->stepX) / 2)
								/ ray->rayDirX;
	else
		trace->perpWallDist = (trace->mapY - sign.posY + (1 - trace->stepY) / 2)
								/ ray->rayDirY;
	if (trace->perpWallDist == 0)
		trace->perpWallDist += 0.05;
}

int		ft_ray(t_ray *ray)
{
	t_img	img;
	map_cub	sign;
	t_trace	*trace;
	int		i;

	sign = ray->sign;
	trace = &ray->trace;
	move_player(ray);
	i = 0;
	img.img = mlx_new_image(ray->mlx, sign.width, sign.height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	while (i < sign.width)
	{
		ray->CameraX = 2 * i / (double)sign.width - 1;
		ray->rayDirX = ray->dirX + ray->planeX * ray->CameraX;
		ray->rayDirY = ray->dirY + ray->planeY * ray->CameraX;
		trace->mapX = (int)sign.posX;
		trace->mapY = (int)sign.posY;
		init_ray(trace, ray, sign);
		ray_shoot(trace, sign, ray);

		//Calculate height of line to draw on screen
		trace->lineHeight = (int)(sign.height / trace->perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		trace->drawStart = (sign.height - trace->lineHeight) / 2;
		if(trace->drawStart < 0)
			trace->drawStart = 0;
		trace->drawEnd = (trace->lineHeight + sign.height) / 2;
		if(trace->drawEnd >= sign.height)
				trace->drawEnd = sign.height - 1;

		// 	//tex rend

		if (trace->side == 0)
			trace->wallX = sign.posY + trace->perpWallDist * ray->rayDirY;
		else
			trace->wallX = sign.posX + trace->perpWallDist * ray->rayDirX;
		trace->wallX = trace->wallX - floor((trace->wallX));
		int texWidth = 64;
		trace->texX = (int)(trace->wallX * (double)(texWidth));
		if(trace->side == 0 && ray->rayDirX > 0)
			trace->texX = texWidth - trace->texX - 1;
		if(trace->side == 1 && ray->rayDirY < 0)
			trace->texX = texWidth - trace->texX - 1;

		//

		if (sign.map_arr[trace->mapX][trace->mapY] == '2')
		{

		}
		else if (sign.posY > trace->mapY && trace->side && sign.map_arr[trace->mapX][trace->mapY] != '2')
		{
			ft_line2(i, trace->drawStart, trace->drawEnd, &img, trace->texX, &ray->tex.no, trace->lineHeight, trace->side, sign);
		}
		else if (sign.posY < trace->mapY && trace->side && sign.map_arr[trace->mapX][trace->mapY] != '2')
		{
			ft_line2(i, trace->drawStart, trace->drawEnd, &img, trace->texX, &ray->tex.so, trace->lineHeight, trace->side, sign);
		}
		else if (sign.posX > trace->mapX && !trace->side && sign.map_arr[trace->mapX][trace->mapY] != '2')
		{
			ft_line2(i, trace->drawStart, trace->drawEnd, &img, trace->texX, &ray->tex.we, trace->lineHeight, trace->side, sign);
		}
		else if (sign.posX < trace->mapX && !trace->side && sign.map_arr[trace->mapX][trace->mapY] != '2')
		{
			ft_line2(i, trace->drawStart, trace->drawEnd, &img, trace->texX, &ray->tex.ea, trace->lineHeight, trace->side, sign);
		}

		int zz;

		zz = 0;
		while (zz < trace->drawStart)
		{
			my_mlx_pixel_put(&img, i, zz, sign.c);
			zz++;
		}
		zz = trace->drawEnd;
		while (zz < sign.height)
		{
			my_mlx_pixel_put(&img, i, zz, sign.f);
			zz++;
		}
		i++;
	}
	mlx_put_image_to_window(ray->mlx, ray->win, img.img, 0, 0);
	return (0);
}

int		loop_main(t_ray *ray)
{
	map_cub *sign;

	sign = &ray->sign;
	ray->mlx = mlx_init();
	ray->win = mlx_new_window(ray->mlx, sign->width, sign->height, "CUB3D");
	parse_color_f(ray, sign->F, sign);
	parse_color_c(ray, sign->C, sign);
	init_textures(ray);
	mlx_hook(ray->win, 2, 0, &key_pressed, ray);
	mlx_hook(ray->win, 17, 0, finish, ray);
	mlx_hook(ray->win, 3, 0, &key_unpressed, ray);
	mlx_loop_hook(ray->mlx, ft_ray, ray);
	mlx_loop(ray->mlx);
	return (0);
}
