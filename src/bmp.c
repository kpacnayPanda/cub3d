/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 23:07:21 by mrosette          #+#    #+#             */
/*   Updated: 2021/04/28 17:10:50 by mrosette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub.h"

int	first_frame(t_ray *ray, t_img img)
{
	t_map_cub	*sign;
	t_trace		*trace;

	sign = &ray->sign;
	trace = &ray->trace;
	init_graph(ray);
	ray_start(ray, trace, *sign, img);
	mlx_put_image_to_window(ray->mlx, ray->win, img.img, 0, 0);
	return (0);
}

char	*make_bm(t_ray ray, int fd)
{
	char	*bm;

	bm = (char *)ft_calloc(sizeof(char), 54);
	if (!(bm))
	{
		close(fd);
		error_handler(5);
	}
	bm[0] = 'B';
	bm[1] = 'M';
	*((int *)(bm + 2)) = ray.sign.width * ray.sign.height * 4 + 54;
	*((int *)(bm + 10)) = 54;
	*((int *)(bm + 14)) = 40;
	*((int *)(bm + 18)) = ray.sign.width;
	*((int *)(bm + 22)) = -ray.sign.height;
	*(bm + 26) = 1;
	*(bm + 28) = 32;
	return (bm);
}

void	img_to_bmp(t_ray ray, int fd, t_img img)
{
	int	i;
	int	j;

	j = 0;
	while (j < ray.sign.height)
	{
		i = 0;
		while (i < ray.sign.width)
		{
			ray.trace.color = *(int *)(img.addr + (j * img.l_len + i * \
							(img.bpr / 8)));
			write(fd, &ray.trace.color, 4);
			i++;
		}
		j++;
	}
}

void	bmp(char *file)
{
	int		fd;
	t_ray	ray;
	char	*bm;
	t_img	img;
	t_spvar	svar;

	cub_start(file, &ray);
	ft_set_spvars(&ray, &svar, &img);
	check_size(&ray, &ray.sign);
	ray.win = mlx_new_window(ray.mlx, ray.sign.width, ray.sign.height, "CUB3D");
	img.img = mlx_new_image(ray.mlx, ray.sign.width, ray.sign.height);
	img.addr = mlx_get_data_addr(img.img, &img.bpr, &img.l_len, &img.end);
	first_frame(&ray, img);
	fd = open("maze.bmp", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	if (fd == -1)
	{
		close(fd);
		error_handler(6);
	}
	bm = (char *)make_bm(ray, fd);
	write(fd, bm, 54);
	free(bm);
	img_to_bmp(ray, fd, img);
	close(fd);
}
