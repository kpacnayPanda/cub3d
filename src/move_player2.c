/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 17:41:39 by mrosette          #+#    #+#             */
/*   Updated: 2021/04/10 18:23:25 by mrosette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub.h"

int		check_for_wall(t_ray *ray,double dir, char ax)
{
	map_cub *sign;

	sign = &ray->sign;
	if (ax == 'x')
	{
		if (sign->map_arr[(int)(sign->posX + dir * ray->movespeed - 0.1 *
					(dir < 0) + 0.1 * (dir > 0))][(int)sign->posY] == '0')
			return (1);
	}
	if (ax == 'y')
	{
		if (sign->map_arr[(int)sign->posX][(int)(sign->posY + dir *
				ray->movespeed - 0.1 * (dir < 0) + 0.1 * (dir > 0))] == '0')
			return (1);
	}
	return (0);
}

void	move_left(t_ray *ray)
{
	double olddir;
	double oldplanex;

	olddir = ray->dirX;
	oldplanex = ray->planeX;
	ray->dirX = ray->dirX * cos(ray->rotspeed) - ray->dirY * sin(ray->rotspeed);
	ray->dirY = olddir * sin(ray->rotspeed) + ray->dirY * cos(ray->rotspeed);
	ray->planeX = ray->planeX * cos(ray->rotspeed) - ray->planeY
							* sin(ray->rotspeed);
	ray->planeY = oldplanex * sin(ray->rotspeed) + ray->planeY
							* cos(ray->rotspeed);
}

void	move_right(t_ray *ray)
{
	double olddir;
	double oldplanex;

	olddir = ray->dirX;
	oldplanex = ray->planeX;
	ray->dirX = ray->dirX * cos(-ray->rotspeed) - ray->dirY
							* sin(-ray->rotspeed);
	ray->dirY = olddir * sin(-ray->rotspeed) + ray->dirY * cos(-ray->rotspeed);
	ray->planeX = ray->planeX * cos(-ray->rotspeed) - ray->planeY
							* sin(-ray->rotspeed);
	ray->planeY = oldplanex * sin(-ray->rotspeed) + ray->planeY
							* cos(-ray->rotspeed);
}
