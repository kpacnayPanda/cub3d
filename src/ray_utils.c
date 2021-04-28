/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 17:53:25 by mrosette          #+#    #+#             */
/*   Updated: 2021/04/27 22:45:57 by mrosette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub.h"

void	init_ray0(t_trace *trace, t_ray *ray, map_cub sign)
{
	ray->CameraX = 2 * ray->i / (double)sign.width - 1;
	ray->rayDirX = ray->dirX + ray->planeX * ray->CameraX;
	ray->rayDirY = ray->dirY + ray->planeY * ray->CameraX;
	trace->mapX = sign.posX;
	trace->mapY = sign.posY;
	trace->deltaDistX = fabs(1 / ray->rayDirX);
	trace->deltaDistY = fabs(1 / ray->rayDirY);
	trace->hit = 0;
	trace->side = -1;
	init_ray1(trace, ray, sign);
}

unsigned int	get_color(t_img *data, int x, int y)
{
	char	*dst;

	dst = data->addr + (y * data->l_len + x * (data->bpr / 8));
	return (*(unsigned int *)dst);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, unsigned int color)
{
	char	*dst;

	dst = img->addr + (y * img->l_len + x * (img->bpr / 8));
	*(unsigned int *)dst = color;
}

int	key_pressed(int keycode, t_ray *ray)
{
	if (keycode == W)
		ray->key.w = 1;
	if (keycode == SS)
		ray->key.s = 1;
	if (keycode == A)
		ray->key.a = 1;
	if (keycode == D)
		ray->key.d = 1;
	if (keycode == LEFT)
		ray->key.left = 1;
	if (keycode == RIGHT)
		ray->key.right = 1;
	if (keycode == EXIT)
		finish(ray);
	return (0);
}

int	key_unpressed(int keycode, t_ray *ray)
{
	if (keycode == W)
		ray->key.w = 0;
	if (keycode == SS)
		ray->key.s = 0;
	if (keycode == A)
		ray->key.a = 0;
	if (keycode == D)
		ray->key.d = 0;
	if (keycode == LEFT)
		ray->key.left = 0;
	if (keycode == RIGHT)
		ray->key.right = 0;
	return (0);
}
