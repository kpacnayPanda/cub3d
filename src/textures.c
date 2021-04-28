/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 17:03:11 by mrosette          #+#    #+#             */
/*   Updated: 2021/04/27 18:53:34 by mrosette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub.h"

void	init_sp(t_ray *ray)
{
	ray->tex.sp.img = mlx_xpm_file_to_image(ray->mlx, "pics/barrel.xpm", \
					&ray->tex.sp.w, &ray->tex.sp.h);
	ray->tex.sp.addr = mlx_get_data_addr(ray->tex.sp.img, &ray->tex.sp.bpr, \
					&ray->tex.sp.l_len, &ray->tex.sp.end);
}

void	init_textures(t_ray *ray)
{
	t_img	t1;
	t_img	t2;
	t_img	t3;
	t_img	t4;
	t_tex	texes;

	t1.img = mlx_xpm_file_to_image(ray->mlx, "pics/brick.xpm", &t1.w, &t1.h);
	t1.addr = mlx_get_data_addr(t1.img, &t1.bpr, &t1.l_len, &t1.end);
	t2.img = mlx_xpm_file_to_image(ray->mlx, "pics/mountain.xpm", &t2.w, &t2.h);
	t2.addr = mlx_get_data_addr(t2.img, &t2.bpr, &t2.l_len, &t2.end);
	t3.img = mlx_xpm_file_to_image(ray->mlx, "pics/eagle.xpm", &t3.w, &t3.h);
	t3.addr = mlx_get_data_addr(t3.img, &t3.bpr, &t3.l_len, &t3.end);
	t4.img = mlx_xpm_file_to_image(ray->mlx, "pics/metal.xpm", &t4.w, &t4.h);
	t4.addr = mlx_get_data_addr(t4.img, &t4.bpr, &t4.l_len, &t4.end);
	texes.no = t1;
	texes.so = t2;
	texes.we = t3;
	texes.ea = t4;
	ray->tex = texes;
}
