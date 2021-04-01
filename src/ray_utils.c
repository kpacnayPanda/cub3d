/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 17:53:25 by mrosette          #+#    #+#             */
/*   Updated: 2021/04/01 18:23:16 by mrosette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub.h"

unsigned int	get_color(t_img *data, int x, int y)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	return (*(unsigned int*)dst);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, unsigned int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	ft_line2(int i, int drawStart, int drawEnd, t_img *img, int texX, t_img *wood, int lineHeight, int side, map_cub sign)
{
	unsigned int color;
	double texPos;
	double step = 1.0 * 64 / lineHeight;
	double drawing;
	drawing = (double)drawStart;
	int tex_y;
	texPos = (drawStart - sign.height / 2 + lineHeight / 2) * step;
	while (drawStart < drawEnd)
	{
		if (texPos > ((double)64 - 1))
			texPos = 64 - 1;
		if (texPos < 0)
			texPos = 0;
			tex_y = (int)texPos;
		color = ((int*)wood->addr)[64 * tex_y + texX];
		my_mlx_pixel_put(img, i, drawStart, color);
		drawStart ++;
		texPos += step ;
	}
}

int		key_pressed(int keycode, t_ray *ray)
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

int		key_unpressed(int keycode, t_ray *ray)
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
