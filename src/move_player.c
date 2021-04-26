/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 16:56:07 by mrosette          #+#    #+#             */
/*   Updated: 2021/04/26 13:54:09 by mrosette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub.h"

void	key_a(t_ray *ray)
{
	map_cub *sign;
	double posx;
	double posy;

	sign = &(ray->sign);
	posx = sign->posX + ray->dirY * ray->movespeed;
	posy = sign->posY - ray->dirX * ray->movespeed;
	if (check_for_wall(posx, sign, 'x'))
		sign->posX += ray->dirY * ray->movespeed;
	if (check_for_wall(posy, sign, 'y'))
		sign->posY -= ray->dirX * ray->movespeed;
}

void	key_w(t_ray *ray)
{
	map_cub *sign;
	double posx;
	double posy;

	sign = &(ray->sign);
	posx = sign->posX + ray->dirX * ray->movespeed;
	posy = sign->posY + ray->dirY * ray->movespeed;
	if (check_for_wall(posx, sign, 'x'))
		sign->posX += ray->dirX * ray->movespeed;
	if (check_for_wall(posy, sign, 'y'))
		sign->posY += ray->dirY * ray->movespeed;
}

void	key_s(t_ray *ray)
{
	map_cub *sign;
	double posx;
	double posy;

	sign = &(ray->sign);
	posx = sign->posX - ray->dirX * ray->movespeed;
	posy = sign->posY - ray->dirY * ray->movespeed;
	if (check_for_wall(posx, sign, 'x'))
		sign->posX -= ray->dirX * ray->movespeed;
	if (check_for_wall(posy, sign,'y'))
		sign->posY -= ray->dirY * ray->movespeed;
}

void	key_d(t_ray *ray)
{
	map_cub *sign;
	double posx;
	double posy;

	sign = &(ray->sign);
	posx = sign->posX - ray->dirY * ray->movespeed;
	posy = sign->posY + ray->dirX * ray->movespeed;
	if (check_for_wall(posx, sign, 'x'))
	{
		sign->posX -= ray->dirY * ray->movespeed;
	}
	if (check_for_wall(posy, sign, 'y'))
	{
		sign->posY += ray->dirX * ray->movespeed;
	}
}

void	move_player(t_ray *ray)
{
	if (ray->key.exit)
		exit(0);
	if (ray->key.w)
		key_w(ray);
	if (ray->key.s)
		key_s(ray);
	if (ray->key.a)
		key_a(ray);
	if (ray->key.d)
		key_d(ray);
	if (ray->key.left)
		move_left(ray);
	if (ray->key.right)
		move_right(ray);
}
