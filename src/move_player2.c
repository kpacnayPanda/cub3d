/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 17:41:39 by mrosette          #+#    #+#             */
/*   Updated: 2021/04/28 16:10:53 by mrosette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub.h"

int	check_for_wall(double pos, t_map_cub *sign, char ax)
{
	if (ax == 'x')
	{
		if (sign->map_arr[(int)(sign->posY)][(int)(pos + 0.1)] == '0' &&
				sign->map_arr[(int)(sign->posY)][(int)(pos - 0.1)] == '0')
			return (1);
	}
	if (ax == 'y')
	{
		if (sign->map_arr[(int)(pos + 0.1)][(int)(sign->posX)] == '0' &&
				sign->map_arr[(int)(pos - 0.1)][(int)(sign->posX)] == '0')
			return (1);
	}
	return (0);
}

void	move_left(t_ray *ray)
{
	double	olddir;
	double	oldplanex;

	olddir = ray->dirX;
	oldplanex = ray->planeX;
	ray->dirX = ray->dirX * cos(-ray->rotspeed) - ray->dirY \
							* sin(-ray->rotspeed);
	ray->dirY = olddir * sin(-ray->rotspeed) + ray->dirY * cos(-ray->rotspeed);
	ray->planeX = ray->planeX * cos(-ray->rotspeed) - ray->planeY \
							* sin(-ray->rotspeed);
	ray->planeY = oldplanex * sin(-ray->rotspeed) + ray->planeY \
							* cos(-ray->rotspeed);
}

void	move_right(t_ray *ray)
{
	double	olddir;
	double	oldplanex;

	olddir = ray->dirX;
	oldplanex = ray->planeX;
	ray->dirX = ray->dirX * cos(ray->rotspeed) - ray->dirY \
							* sin(ray->rotspeed);
	ray->dirY = olddir * sin(ray->rotspeed) + ray->dirY * cos(ray->rotspeed);
	ray->planeX = ray->planeX * cos(ray->rotspeed) - ray->planeY \
							* sin(ray->rotspeed);
	ray->planeY = oldplanex * sin(ray->rotspeed) + ray->planeY \
							* cos(ray->rotspeed);
}
