/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 17:03:11 by mrosette          #+#    #+#             */
/*   Updated: 2021/03/24 19:05:41 by mrosette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub.h"

void	init_textures(t_ray *ray)
{
	t_img tex1;
	t_img tex2;
	t_img tex3;
	t_img tex4;
	t_img sp;

	t_tex texes;

	tex1.img = mlx_xpm_file_to_image(ray->mlx, "pics/stone.xpm", &tex1.width, &tex1.height);
	tex1.addr = mlx_get_data_addr(tex1.img, &tex1.bits_per_pixel, &tex1.line_length, &tex1.endian);
	tex2.img = mlx_xpm_file_to_image(ray->mlx, "pics/mossy.xpm", &tex2.width, &tex2.height);
	tex2.addr = mlx_get_data_addr(tex2.img, &tex2.bits_per_pixel, &tex2.line_length, &tex2.endian);
	tex3.img = mlx_xpm_file_to_image(ray->mlx, "pics/creeper.xpm", &tex3.width, &tex3.height);
	tex3.addr = mlx_get_data_addr(tex3.img, &tex3.bits_per_pixel, &tex3.line_length, &tex3.endian);
	tex4.img = mlx_xpm_file_to_image(ray->mlx, "pics/rikardo.xpm", &tex4.width, &tex4.height);
	tex4.addr = mlx_get_data_addr(tex4.img, &tex4.bits_per_pixel, &tex4.line_length, &tex4.endian);
	sp.img = mlx_xpm_file_to_image(ray->mlx, "pics/barrel.xpm", &sp.width, &sp.height);
	sp.addr = mlx_get_data_addr(sp.img, &sp.bits_per_pixel, &sp.line_length, &sp.endian);

	texes.no = tex1;
	texes.so = tex2;
	texes.we = tex3;
	texes.ea = tex4;
	texes.sp = sp;

	ray->tex = texes;
}
