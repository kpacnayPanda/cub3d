/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 19:36:41 by mrosette          #+#    #+#             */
/*   Updated: 2021/04/26 12:49:32 by mrosette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub.h"

void	ft_line2(t_ray *ray, t_img *img, t_img *wood, t_trace *trace, int y)
{
		trace->tex_y = (int)trace->texPos & (64 - 1);
		trace->color = ((int*)wood->addr)[64 * trace->tex_y + trace->texX];
		my_mlx_pixel_put(img, ray->i, y, trace->color);
}

void	draw_walls(t_trace *trace, map_cub sign, t_ray *ray, t_img *img)
{
	int y;

	y = trace->drawStart;
	if (trace->side == 0)
	{
		trace->step = 1.0 * 64 / trace->lineh;
		trace->texX = 64 - trace->texX - 1;
	}
	else
	{
		trace->step = 1.0 * 64 / trace->lineh;
		trace->texX = 64 - trace->texX - 1;
	}
	trace->texPos = (trace->drawStart - sign.height / 2 + trace->lineh / 2) * trace->step;
	while (y < trace->drawEnd)
	{
		trace->texPos += trace->step;
		if (trace->side == 0)
		{
			if (trace->stepX < 0)
				ft_line2(ray, img, &ray->tex.ea, trace, y);
			else
				ft_line2(ray, img, &ray->tex.we, trace, y);
		}
		else
		{
			if (trace->stepY < 0)
				ft_line2(ray, img, &ray->tex.so, trace, y);
			else
				ft_line2(ray, img, &ray->tex.no, trace, y);
		}
		y++;
	}
}

void	draw_f_c(t_trace *trace, t_img img, map_cub sign, t_ray *ray)
{
	int zz;

	zz = 0;
	while (zz < trace->drawStart)
	{
		my_mlx_pixel_put(&img, ray->i, zz, sign.c);
		zz++;
	}
	zz = trace->drawEnd;
	while (zz < sign.height)
	{
		my_mlx_pixel_put(&img, ray->i, zz, sign.f);
		zz++;
	}
}
