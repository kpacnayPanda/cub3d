/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 13:18:54 by mrosette          #+#    #+#             */
/*   Updated: 2021/04/26 14:10:02 by mrosette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub.h"

void	get_sp_pos(t_ray *ray, int count, int i, int j)
{
	if (!(ray->sprite[count] = (t_sprite*)malloc(sizeof(t_sprite))))
		error_handler(6);
	ray->sprite[count]->x = (double)j + 0.5;
	ray->sprite[count]->y = (double)i + 0.5;
}

void	init_sprite(t_ray *ray)
{
	int i;
	int j;
	int count;
	map_cub *sign;

	i = 0;
	count = 0;
	sign = &ray->sign;
	ray->sprite = (t_sprite**)malloc(sizeof(t_sprite*) *
							(ray->sign.spp_count + 1));
	if (!ray->sprite)
		error_handler(6);
	while(i < sign->mapheight)
	{
		j = 0;
		while (j < sign->mapwidth)
		{
			if (sign->map_arr[i][j] == '2')
			{
				get_sp_pos(ray, count, i, j);
				count++;
			}
			j++;
		}
		i++;
	}
	ray->sprite[count] = NULL;
}

void	sprite_sorting(int *order, double *dist, int count)
{
	int i;
	int j;
	double tmp;

	i = 0;
	if (count == 0)
		return;
	int check = 1;
	while (check)
	{
		i = 0;
		check = 0;
	while (i < count - 1)
	{
		j = i + 1;
			if (dist[i] < dist[j])
			{
				tmp = dist[i];
				dist[i] = dist[j];
				dist[j] = tmp;
				tmp = order[i];
				order[i] = order[j];
				order[j] = tmp;
				check = 1;
			}
		i++;
	}
	}
}

void	sprite_rendering(t_ray *ray, double *dis_buff, t_img *img, t_img *wood)
{
	int count;
	int i;
	t_sprite **sprite;
	t_trace *trace;
	int	order[ray->sign.spp_count];
	double dist[ray->sign.spp_count];

	printf("%f\n", ray->dirX);
	printf("%f\n", ray->dirY);
	//exit (0);

	sprite = ray->sprite;
	trace = &ray->trace;
	i = 0;
	count = ray->sign.spp_count;
	while (i < count)
	{
		order[i] = i;
		// printf("%f\n", sprite[i]->x);
		// printf("%f\n", sprite[i]->y);
		dist[i] = pow((ray->sign.posX - sprite[i]->x), 2);
		dist[i] += pow((ray->sign.posY - sprite[i]->y), 2);
		// printf("%f\n", sprite[order[i]]->x);
		// printf("%f\n", sprite[order[i]]->y);
		// printf("%f\n", dist[i]);
		i++;
	}
	sprite_sorting(order, dist, count);
	// printf("\n\n");
	// printf("%f\n", sprite[0]->x);
	// 	printf("%f\n", sprite[0]->y);
		printf("%f\n", dist[0]);
		// exit (0);

	i = 0;
	while (i < count)
	{
		// printf("%f\n", sprite[order[i]]->x);
		// printf("%f\n", sprite[order[i]]->y);
		// exit (0);
		double spriteX = sprite[order[i]]->x - ray->sign.posX;
		double spriteY = sprite[order[i]]->y - ray->sign.posY;

		double invdet = 1.0 / (ray->planeX * ray->dirY - ray->dirX * ray->planeY);

		double transX = invdet * (ray->dirY * spriteX - ray->dirX * spriteY);
		double transY = invdet * (-ray->planeY * spriteX + ray->planeX * spriteY);

		int spritescreen = (int)((ray->sign.width / 2) * (1 + transX / transY));

		int spheight = abs((int)(ray->sign.height / transY));

		int drawStartY = -spheight / 2 + ray->sign.height / 2;
		if (drawStartY < 0)
			drawStartY = 0;
		int drawEndy = spheight / 2 + ray->sign.height / 2;
		if (drawEndy >= ray->sign.height)
			drawEndy = ray->sign.height - 1;

		int spwidth = abs((int)(ray->sign.height / transY));
		int drawstartX = -spwidth / 2 + spritescreen;
		if (drawstartX < 0)
			drawstartX = 0;
		int drawEndx = spwidth / 2 + spritescreen;
		if (drawEndx >= ray->sign.width)
			drawEndx = ray->sign.width - 1;

		int stripe = drawstartX;
		while (stripe < drawEndx)
		{
			int texX = (int)(256 * (stripe - (-spwidth / 2 + spritescreen)) * 64 / spwidth) / 256;
			if (transY > 0 && stripe > 0 && stripe < ray->sign.width && transY < dis_buff[stripe])
			{
				int y = drawStartY;
				while (y < drawEndy)
				{
					int d = (y) * 256 - ray->sign.height * 128 + spheight * 128;
					int texY = ((d * 64) / spheight) / 256;
					int color = ((int*)wood->addr)[(int)(64 * texY + texX)];
					if ((color & 0x00FFFFFF) != 0)
						my_mlx_pixel_put(img, stripe, y, color);
					y++;
				}
			}
			stripe++;
		}
		i++;
	}
}
