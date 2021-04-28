/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 17:03:11 by mrosette          #+#    #+#             */
/*   Updated: 2021/04/28 16:11:45 by mrosette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub.h"

void	init_sp(t_ray *ray)
{
	char	*path;

	path = ray->sign.S;
	ray->tex.sp.img = mlx_xpm_file_to_image(ray->mlx, path, \
					&ray->tex.sp.w, &ray->tex.sp.h);
	if (ray->tex.sp.img == NULL)
		error_handler(4);
	ray->tex.sp.addr = mlx_get_data_addr(ray->tex.sp.img, &ray->tex.sp.bpr, \
					&ray->tex.sp.l_len, &ray->tex.sp.end);
}

void	init_no(t_ray *ray)
{
	char	*tex;

	tex = ray->sign.NO;
	ray->tex.no.img = mlx_xpm_file_to_image(ray->mlx, tex, \
					&ray->tex.no.w, &ray->tex.no.h);
	if (ray->tex.no.img == NULL)
		error_handler(7);
	ray->tex.no.addr = mlx_get_data_addr(ray->tex.no.img, &ray->tex.no.bpr, \
					&ray->tex.no.l_len, &ray->tex.no.end);
}

void	init_textures(t_ray *ray)
{
	t_img	t2;
	t_img	t3;
	t_img	t4;
	t_tex	texes;

	t2.img = mlx_xpm_file_to_image(ray->mlx, ray->sign.SO, &t2.w, &t2.h);
	if (t2.img == NULL)
		error_handler(7);
	t2.addr = mlx_get_data_addr(t2.img, &t2.bpr, &t2.l_len, &t2.end);
	t3.img = mlx_xpm_file_to_image(ray->mlx, ray->sign.WE, &t3.w, &t3.h);
	if (t3.img == NULL)
		error_handler(7);
	t3.addr = mlx_get_data_addr(t3.img, &t3.bpr, &t3.l_len, &t3.end);
	t4.img = mlx_xpm_file_to_image(ray->mlx, ray->sign.EA, &t4.w, &t4.h);
	if (t4.img == NULL)
		error_handler(7);
	t4.addr = mlx_get_data_addr(t4.img, &t4.bpr, &t4.l_len, &t4.end);
	texes.so = t2;
	texes.we = t3;
	texes.ea = t4;
	ray->tex = texes;
}

void	init_graph(t_ray *ray)
{
	parse_color_f(ray, ray->sign.F, &ray->sign);
	parse_color_c(ray, ray->sign.C, &ray->sign);
	init_no(ray);
	init_textures(ray);
	init_sp(ray);
}
