/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 17:03:11 by mrosette          #+#    #+#             */
/*   Updated: 2021/04/01 21:03:34 by mrosette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub.h"

void	init_sp(t_ray *ray)
{
	t_img	sp;
	t_tex	texes;

	sp.img = mlx_xpm_file_to_image(ray->mlx, "pics/barrel.xpm", &sp.width, &sp.height);
	sp.addr = mlx_get_data_addr(sp.img, &sp.bpr, &sp.l_len, &sp.endian);
	texes.sp = sp;
	ray->tex = texes;
}

void	init_textures(t_ray *ray)
{
	t_img	tex1;
	t_img	tex2;
	t_img	tex3;
	t_img	tex4;
	t_tex	texes;

	tex1.img = mlx_xpm_file_to_image(ray->mlx, "pics/brick.xpm", &tex1.width, &tex1.height);
	tex1.addr = mlx_get_data_addr(tex1.img, &tex1.bpr, &tex1.l_len, &tex1.endian);
	tex2.img = mlx_xpm_file_to_image(ray->mlx, "pics/mountains.xpm", &tex2.width, &tex2.height);
	tex2.addr = mlx_get_data_addr(tex2.img, &tex2.bpr, &tex2.l_len, &tex2.endian);
	tex3.img = mlx_xpm_file_to_image(ray->mlx, "pics/eagle.xpm", &tex3.width, &tex3.height);
	tex3.addr = mlx_get_data_addr(tex3.img, &tex3.bpr, &tex3.l_len, &tex3.endian);
	texes.no = tex1;
	texes.so = tex2;
	texes.we = tex3;
	texes.ea = tex4;
	ray->tex = texes;
	init_sp(ray);
}
