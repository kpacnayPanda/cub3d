/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 15:27:16 by mrosette          #+#    #+#             */
/*   Updated: 2021/04/28 17:00:59 by mrosette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub.h"

void	error_handler(int err)
{
	if (err == 1)
		ft_putendl_fd("INVALID ARGUMENTS", 0);
	if (err == 2)
		ft_putendl_fd("INVALID CONFIG OR MAP", 0);
	if (err == 3)
		ft_putendl_fd("INVALID MAP", 0);
	if (err == 4)
		ft_putendl_fd("FILE NOT FOUND", 0);
	if (err == 5)
		ft_putendl_fd("COLOR ERROR", 0);
	if (err == 6)
		ft_putendl_fd("SOMETHING WENT WRONG", 0);
	if (err == 7)
		ft_putendl_fd("XPMFILE NOT FOUND", 0);
	exit(0);
}

void	check_before_map(t_map_cub *sign, char *line)
{
	if (!sign->NO || !sign->SO || !sign->WE || !sign->EA || !sign->F || !sign->C
		|| !sign->S || sign->height == 0 || sign->width == 0)
		error_handler(2);
}

void	check_for_valid(t_map_cub *sign)
{
	if (!sign->NO || !sign->SO || !sign->WE || !sign->EA || !sign->F || !sign->C
		|| !sign->S || sign->height == 0 || sign->width == 0)
		error_handler(2);
	if (sign->mapwidth == 0 || sign->posX == -1 || sign->posY == -1)
		error_handler(3);
	if (sign->height < 1 || sign->width < 1)
		error_handler(2);
}

void	check_size(t_ray *ray, t_map_cub *sign)
{
	int	h;
	int	w;

	mlx_get_screen_size(ray->mlx, &w, &h);
	if (sign->width < 100)
		sign->width = 100;
	if (sign->width > w)
		sign->width = w;
	if (sign->height < 100)
		sign->height = 100;
	if (sign->height > h)
		sign->height = h;
}
