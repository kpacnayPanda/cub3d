/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 23:52:55 by mrosette          #+#    #+#             */
/*   Updated: 2021/04/25 13:25:34 by mrosette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub.h"

void	draw_sprite_calculate(t_ray *ray)
{
	ray->sp_height = abs((int)(ray->sign.height / ray->transy));
	ray->sp_width = abs((int)(ray->sign.height / ray->transy));
	ray->drawsy = (ray->sign.height - ray->sp_height) / 2;
	if (ray->drawsy < 0)
		ray->drawsy = 0;
	ray->drawey = (ray->sign.height + ray->sp_height) / 2;
	if (ray->drawey >= ray->sign.height)
		ray->drawey = ray->sign.height -1;
	ray->drawsx = ray->sp_screen - ray->sp_width / 2;
	if (ray->drawsx < 0)
		ray->drawsx = 0;
	ray->drawex = ray->sp_screen + ray->sp_width / 2;
	if (ray->drawex >= ray->sign.width)
		ray->drawex = ray->sign.width - 1;
}

void	sp_pixel_put(t_ray *ray, int i, int j)
{
	int color;

	ray->trace.tex_y = (int)((i - (ray->sign.height - ray->sp_height) / 2) *
						ray->tex.sp.h / ray->sp_height);
						printf("kek\n");
	color = ((int*)ray->tex.sp.addr)[64 * ray->trace.tex_y + ray->trace.texX];
	if ((color & 0x00FFFFFF) != 0)
		my_mlx_pixel_put(&ray->tex.sp, i, j, color);
}

void	sprite_draw(t_ray *ray, double *dist_buff)
{
	int i;
	int j;

	i = ray->drawsx;
	while (i < ray->drawex)
	{
		ray->trace.texX = (int)((i - (ray->sp_screen - ray->sp_width / 2)) *
								ray->tex.sp.w / ray->sp_width);
		if (ray->transy > 0 && ray->transy < dist_buff[i] && i > 0 && i
								< ray->sign.width)
		{
			j = ray->drawsy;
			while (j < ray->drawey)
			{
				sp_pixel_put(ray, i, j);
				j++;
			}
		}
		i++;
	}
}

void	sprite_rend2(t_ray *ray, int count, double *dist_buff)
{
	t_sprite **sprite;
	double inv_det;

	sprite = ray->sprite;
	inv_det = 1.0 / (-ray->planeX * ray->dirY + ray->dirX * ray->planeX);
	ray->transx = inv_det * (ray->dirY * sprite[count]->dist_x - ray->dirX *
							sprite[count]->dist_y);
	ray->transy = inv_det * (ray->planeY * sprite[count]->dist_x - ray->planeX *
							sprite[count]->dist_y);
	ray->sp_screen = (int)(ray->sign.width / 2) *
						(1 + ray->transx / ray->transy);
	draw_sprite_calculate(ray);
	sprite_draw(ray, dist_buff);
}
