/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 13:18:54 by mrosette          #+#    #+#             */
/*   Updated: 2021/04/28 01:11:13 by mrosette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub.h"

void	get_sp_pos(t_ray *ray, int count, int i, int j)
{
	ray->sprite[count] = (t_sprite *)malloc(sizeof(t_sprite));
	if (!ray->sprite)
		error_handler(6);
	ray->sprite[count]->x = (double)j + 0.5;
	ray->sprite[count]->y = (double)i + 0.5;
}

void	init_sprite(t_ray *ray, int count)
{
	int		i;
	int		j;
	map_cub	*sign;

	i = 0;
	sign = &ray->sign;
	ray->sprite = (t_sprite **)malloc(sizeof(t_sprite *) * \
							(ray->sign.spp_count + 1));
	if (!ray->sprite)
		error_handler(6);
	while (i < sign->mapheight)
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

void	sprite_sorting(int *order, double *dist, int count, int check)
{
	int		i;
	double	tmp;

	if (count == 0)
		return ;
	while (check)
	{
		i = 0;
		check = 0;
		while (i < count - 1)
		{
			if (dist[i] < dist[i + 1])
			{
				tmp = dist[i];
				dist[i] = dist[i + 1];
				dist[i + 1] = tmp;
				tmp = order[i];
				order[i] = order[i + 1];
				order[i + 1] = tmp;
				check = 1;
			}
			i++;
		}
	}
}

void	ft_set_spvars(t_ray *ray, t_spvar *svar, t_img *img)
{
	ray->spvar = *svar;
	ray->img = *img;
}
