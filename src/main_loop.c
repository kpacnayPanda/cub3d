/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 16:27:17 by mrosette          #+#    #+#             */
/*   Updated: 2021/04/28 02:28:26 by mrosette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub.h"

void	prepare_draw(t_trace *trace, t_ray *ray, map_cub sign)
{
	int	texwidth;

	texwidth = 64;
	trace->lineh = (int)(sign.height / trace->perpWallDist);
	trace->drawStart = (sign.height - trace->lineh) / 2;
	if (trace->drawStart < 0)
		trace->drawStart = 0;
	trace->drawEnd = (trace->lineh + sign.height) / 2;
	if (trace->drawEnd >= sign.height)
		trace->drawEnd = sign.height - 1;
	if (trace->side == 0)
		trace->wallX = sign.posY + trace->perpWallDist * ray->rayDirY;
	else
		trace->wallX = sign.posX + trace->perpWallDist * ray->rayDirX;
	trace->wallX -= (int)trace->wallX;
	trace->texX = (int)(trace->wallX * (double)(texwidth));
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
		if (sign.map_arr[trace->mapY][trace->mapX] == '1')
			trace->hit = 1;
	}
	if (trace->side == 0)
		trace->perpWallDist = (trace->mapX - sign.posX + (1 - trace->stepX) \
		/ 2) / ray->rayDirX;
	else
		trace->perpWallDist = (trace->mapY - sign.posY + (1 - trace->stepY) \
		/ 2) / ray->rayDirY;
	prepare_draw(trace, ray, sign);
}

void	ray_start(t_ray *ray, t_trace *trace, map_cub sign, t_img img)
{
	double	*dis_buff;

	ray->i = 0;
	dis_buff = (double *)malloc(sizeof(double) * ray->sign.width);
	while (ray->i < sign.width)
	{
		init_ray0(trace, ray, sign);
		draw_walls(trace, sign, ray, &img);
		draw_f_c(trace, img, sign, ray);
		dis_buff[ray->i] = trace->perpWallDist;
		ray->i++;
	}
	sprite_rendering(ray, dis_buff, &img);
	free(dis_buff);
}

int	ft_ray(t_ray *ray)
{
	t_img	img;
	map_cub	sign;
	t_trace	*trace;

	sign = ray->sign;
	trace = &ray->trace;
	img.img = mlx_new_image(ray->mlx, sign.width, sign.height);
	img.addr = mlx_get_data_addr(img.img, &img.bpr, &img.l_len, &img.end);
	move_player(ray);
	ray_start(ray, trace, sign, img);
	mlx_put_image_to_window(ray->mlx, ray->win, img.img, 0, 0);
	mlx_destroy_image(ray->mlx, img.img);
	return (0);
}

int	loop_main(t_ray *ray)
{
	map_cub	*sign;

	sign = &ray->sign;
	ray->mlx = mlx_init();
	ray->win = mlx_new_window(ray->mlx, sign->width, sign->height, "CUB3D");
	parse_color_f(ray, sign->F, sign);
	parse_color_c(ray, sign->C, sign);
	init_textures(ray);
	init_sp(ray);
	mlx_hook(ray->win, 2, 0, &key_pressed, ray);
	mlx_hook(ray->win, 17, 0, finish, ray);
	mlx_hook(ray->win, 3, 0, &key_unpressed, ray);
	mlx_loop_hook(ray->mlx, ft_ray, ray);
	mlx_loop(ray->mlx);
	return (0);
}
