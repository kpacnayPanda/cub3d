/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 23:52:55 by mrosette          #+#    #+#             */
/*   Updated: 2021/04/28 12:51:40 by mrosette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub.h"

void	sp_last(t_ray *ray, double *dis_buff, t_img *img, t_spvar *var)
{
	t_img	*wood;
	int		tex;

	wood = &ray->tex.sp;
	while (var->stripe < var->drawEndx)
	{
		tex = (int)(256 * (var->stripe - (-var->spwidth / 2 + \
				var->spritescreen)) * 64 / var->spwidth) / 256;
		if (var->transY > 0 && var->stripe > 0 && var->stripe < ray->sign.width
			&& var->transY < dis_buff[var->stripe])
		{
			var->y = var->drawStartY;
			while (var->y < var->drawEndy)
			{
				var->d = (var->y) * 256 - ray->sign.height * 128 + \
						var->spheight * 128;
				var->texY = ((var->d * 64) / var->spheight) / 256;
				var->color = ((int *)wood->addr)[(int)(64 * var->texY + tex)];
				if ((var->color & 0x00FFFFFF) != 0)
					my_mlx_pixel_put(img, var->stripe, var->y, var->color);
				var->y++;
			}
		}
		var->stripe++;
	}
}

void	sp_matrix(t_ray *ray, double *dis_buff, t_img *img, t_spvar *var)
{
	var->drawStartY = -var->spheight / 2 + ray->sign.height / 2;
	if (var->drawStartY < 0)
		var->drawStartY = 0;
	var->drawEndy = var->spheight / 2 + ray->sign.height / 2;
	if (var->drawEndy >= ray->sign.height)
		var->drawEndy = ray->sign.height - 1;
	var->spwidth = abs((int)(ray->sign.height / var->transY));
	var->drawstartX = -var->spwidth / 2 + var->spritescreen;
	if (var->drawstartX < 0)
		var->drawstartX = 0;
	var->drawEndx = var->spwidth / 2 + var->spritescreen;
	if (var->drawEndx >= ray->sign.width)
		var->drawEndx = ray->sign.width - 1;
	var->stripe = var->drawstartX;
	sp_last(ray, dis_buff, img, var);
}

void	sprite_rend2(int *order, t_ray *ray, double *dis_buff, t_img *img)
{
	int			i;
	t_sprite	**sprite;
	double		spritex;
	double		spritey;
	t_spvar		*var;

	i = 0;
	sprite = ray->sprite;
	var = &ray->spvar;
	while (i < ray->sign.spp_count)
	{
		spritex = sprite[order[i]]->x - ray->sign.posX;
		spritey = sprite[order[i]]->y - ray->sign.posY;
		var->invdet = 1.0 / (ray->planeX * ray->dirY - ray->dirX * ray->planeY);
		var->transX = var->invdet * (ray->dirY * spritex - ray->dirX * spritey);
		var->transY = var->invdet * (-ray->planeY * spritex \
					+ ray->planeX * spritey);
		var->spritescreen = (int)((ray->sign.width / 2) * \
					(1 + var->transX / var->transY));
		var->spheight = abs((int)(ray->sign.height / var->transY));
		sp_matrix(ray, dis_buff, img, var);
		i++;
	}
}

void	sprite_rendering(t_ray *ray, double *dis_buff, t_img *img)
{
	int			i;
	t_sprite	**sprite;
	t_trace		*trace;
	int			*order;
	double		*dist;

	sprite = ray->sprite;
	trace = &ray->trace;
	order = (int *)malloc(sizeof(int) * ray->sign.spp_count);
	dist = (double *)malloc(sizeof(double) * ray->sign.spp_count);
	i = 0;
	while (i < ray->sign.spp_count)
	{
		order[i] = i;
		dist[i] = pow((ray->sign.posX - sprite[i]->x), 2);
		dist[i] += pow((ray->sign.posY - sprite[i]->y), 2);
		i++;
	}
	sprite_sorting(order, dist, ray->sign.spp_count, 1);
	sprite_rend2(order, ray, dis_buff, img);
	free(order);
	free(dist);
}
