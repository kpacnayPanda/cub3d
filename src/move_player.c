/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 16:56:07 by mrosette          #+#    #+#             */
/*   Updated: 2021/04/10 17:54:41 by mrosette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub.h"

void	key_a(t_ray *ray)
{
	map_cub *sign;

	sign = &(ray->sign);
	if (sign->map_arr[(int)sign->posX]
					[(int)(sign->posY + ray->dirX * ray->movespeed)] == '0')
		sign->posY += ray->dirX * ray->movespeed;
	if (sign->map_arr[(int)(sign->posX - ray->dirY * ray->movespeed)]
					[(int)sign->posY] == '0')
		sign->posX -= ray->dirY * ray->movespeed;
}

void	key_w(t_ray *ray)
{
	map_cub *sign;

	sign = &(ray->sign);
	if (sign->map_arr[(int)(sign->posX + ray->dirX * ray->movespeed)]
					[(int)(sign->posY)] == '0')
		sign->posX += ray->dirX * ray->movespeed;
	if (sign->map_arr[(int)(sign->posX)]
					[(int)(sign->posY + ray->dirY * ray->movespeed)] == '0')
		sign->posY += ray->dirY * ray->movespeed;
}

void	key_s(t_ray *ray)
{
	map_cub *sign;

	sign = &(ray->sign);
	if (sign->map_arr[(int)(sign->posX - ray->dirX * ray->movespeed)]
					[(int)(sign->posY)] == '0')
		sign->posX -= ray->dirX * ray->movespeed;
	if (sign->map_arr[(int)(sign->posX)]
					[(int)(sign->posY - ray->dirY * ray->movespeed)] == '0')
		sign->posY -= ray->dirY * ray->movespeed;
}

void	key_d(t_ray *ray)
{
	map_cub *sign;

	sign = &(ray->sign);
	if (sign->map_arr[(int)sign->posX]
					[(int)(sign->posY - ray->dirX * ray->movespeed)] == '0')
		sign->posY -= ray->dirX * ray->movespeed;
	if (sign->map_arr[(int)(sign->posX + ray->dirY * ray->movespeed)]
					[(int)sign->posY] == '0')
		sign->posX += ray->dirY * ray->movespeed;
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
