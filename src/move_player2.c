/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 17:41:39 by mrosette          #+#    #+#             */
/*   Updated: 2021/04/01 17:45:27 by mrosette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub.h"

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
