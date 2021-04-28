/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 23:07:21 by mrosette          #+#    #+#             */
/*   Updated: 2021/04/28 02:21:29 by mrosette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub.h"

int	first_frame(t_ray *ray, t_img img)
{
	map_cub *sign;
	t_trace	*trace;

	sign = &ray->sign;
	trace = &ray->trace;
	parse_color_f(ray, ray->sign.F, sign);
	parse_color_c(ray, ray->sign.C, sign);
	init_textures(ray);
	init_sp(ray);
	ray_start(ray, trace, *sign, img);
	mlx_put_image_to_window(ray->mlx, ray->win, img.img, 0, 0);
	return (0);
}

static char		*make_bitmap(t_ray ray, int fd)
{
	char *bitmap;

	if (!(bitmap = (char*)ft_calloc(sizeof(char), 54)))
	{
		close(fd);
		error_handler(5);
	}
	bitmap[0] = 'B';
	bitmap[1] = 'M';
	*((int*)(bitmap + 2)) = ray.sign.width * ray.sign.height * 4 + 54;
	*((int*)(bitmap + 10)) = 54;
	*((int*)(bitmap + 14)) = 40;
	*((int*)(bitmap + 18)) = ray.sign.width;
	*((int*)(bitmap + 22)) = -ray.sign.height;
	*(bitmap + 26) = 1;
	*(bitmap + 28) = 32;
	return (bitmap);
}

static void		img_to_bmp(t_ray ray, int fd, t_img img)
{
	int x;
	int y;

	y = 0;
	while (y < ray.sign.height)
	{
		x = 0;
		while (x < ray.sign.width)
		{
			ray.trace.color= *(int*)(img.addr + (y * img.l_len + x *
							(img.bpr / 8)));
			write(fd, &ray.trace.color, 4);
			x++;
		}
		y++;
	}
}

void	bmp(char *file)
{
	int		fd;
	t_ray	ray;
	char	*bitmap;
	t_img	img;

	cub_start(file, &ray);
	ray.mlx = mlx_init();
	ray.win = mlx_new_window(ray.mlx, ray.sign.width, ray.sign.height, "CUB3D");
	img.img = mlx_new_image(ray.mlx, ray.sign.width, ray.sign.height);
	img.addr = mlx_get_data_addr(img.img, &img.bpr, &img.l_len, &img.end);
	first_frame(&ray, img);
	if ((fd = open("maze.bmp", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU)) == -1)
	{
		close(fd);
		error_handler(6);
	}
	bitmap = (char*)make_bitmap(ray, fd);
	write(fd, bitmap,  54);
	free(bitmap);
	img_to_bmp(ray, fd, img);
	close(fd);
}
