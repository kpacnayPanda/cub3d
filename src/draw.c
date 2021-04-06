/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 19:36:41 by mrosette          #+#    #+#             */
/*   Updated: 2021/04/06 16:36:59 by mrosette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub.h"

void	ft_line2(t_ray *ray, t_img *img, t_img *wood, map_cub sign)
{
	int		draws;
	int		drawe;
	t_trace	*trace;

	trace = &ray->trace;
	draws = trace->drawStart;
	drawe = trace->drawEnd;
	trace->step = 1.0 * 64 / trace->lineh;
	trace->drawing = (double)draws;
	trace->texPos = (draws - sign.height / 2 + trace->lineh / 2) * trace->step;
	while (draws < drawe)
	{
		if (trace->texPos > ((double)64 - 1))
			trace->texPos = 64 - 1;
		if (trace->texPos < 0)
			trace->texPos = 0;
		trace->tex_y = (int)trace->texPos;
		trace->color = ((int*)wood->addr)[64 * trace->tex_y + trace->texX];
		my_mlx_pixel_put(img, ray->i, draws, trace->color);
		draws++;
		trace->texPos += trace->step;
	}
}

void	draw_walls(t_trace *trace, map_cub sign, t_ray *ray, t_img *img)
{
	int y;
	int x;

	y = trace->mapY;
	x = trace->mapX;
	if (sign.map_arr[x][y] == '2')
	{
		//draw
	}
	else if (sign.posY > y && trace->side && sign.map_arr[x][y] != '2')
	{
		ft_line2(ray, img, &ray->tex.no, sign);
	}
	else if (sign.posY < y && trace->side && sign.map_arr[x][y] != '2')
	{
		ft_line2(ray, img, &ray->tex.so, sign);
	}
	else if (sign.posX > x && !trace->side && sign.map_arr[x][y] != '2')
	{
		ft_line2(ray, img, &ray->tex.we, sign);
	}
	else if (sign.posX < x && !trace->side && sign.map_arr[x][y] != '2')
	{
		ft_line2(ray, img, &ray->tex.ea, sign);
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
