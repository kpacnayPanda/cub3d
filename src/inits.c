/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 16:11:08 by mrosette          #+#    #+#             */
/*   Updated: 2021/04/01 20:28:52 by mrosette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub.h"

void	ft_set_args(map_cub *sign)
{
	sign->NO = NULL;
	sign->SO = NULL;
	sign->WE = NULL;
	sign->EA = NULL;
	sign->C = NULL;
	sign->F = NULL;
	sign->S = NULL;
	sign->height = 0;
	sign->width = 0;
	sign->mapwidth = 0;
	sign->mapheight = 0;
	sign->iheight = 0;
	sign->flag = 1;
	sign->posX = -1;
	sign->posY = -1;
}

void	ft_set_keys(t_key *key)
{
	key->a = 0;
	key->s = 0;
	key->w = 0;
	key->d = 0;
	key->exit = 0;
	key->left = 0;
	key->right = 0;
}

void	init_st(t_ray *ray, map_cub *sign, t_key *key, t_trace *trace)
{
	ray->win = NULL;
	ray->dirX = -1;
	ray->dirY = 0;
	ray->planeX = 0;
	ray->planeY = 0.66;
	ray->oldtime = 0;
	ray->time = 0;
	ray->CameraX = 0;
	ray->rayDirX = 0;
	ray->rayDirY = 0;
	ray->rotspeed = 0.02;
	ray->movespeed = 0.1;
	ray->sign = *sign;
	ray->key = *key;
	ray->trace = *trace;
}

void	ft_set_trace(t_trace *trace)
{
	trace->perpWallDist = 0;
}
