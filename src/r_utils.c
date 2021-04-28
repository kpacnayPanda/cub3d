/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 17:08:53 by mrosette          #+#    #+#             */
/*   Updated: 2021/04/27 23:51:45 by mrosette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub.h"

void	take_width_r(char *str, int flag, map_cub *sign, int i)
{
	int		widthlen;
	char	*tmp;
	int		num;

	widthlen = 0;
	num = 0;
	while (str[i] != ' ' && str[i] != '\0')
	{
		widthlen++;
		i++;
	}
	tmp = (char *)malloc((widthlen + 1) * sizeof(char));
	i = 0;
	while (str[i] != ' ' && str[i] != '\0')
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = '\0';
	num = ft_atoi(tmp);
	if (flag == 0)
		sign->width = num;
	if (flag == 2)
		sign->height = num;
	free(tmp);
}

void	take_r_specs(char *str, map_cub *sign)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) && (flag == 0))
		{
			take_width_r(&str[i], flag, sign, 0);
			flag = 1;
		}
		if (ft_isdigit(str[i]) && (flag == 2))
		{
			take_width_r(&str[i], flag, sign, 0);
			flag = 3;
		}
		if (str[i] == ' ')
		{
			if (flag == 1)
				flag = 2;
		}
		i++;
	}
}

void	find_sprites(map_cub *sign)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	count = 0;
	while (i < sign->mapheight)
	{
		while (j < sign->mapwidth)
		{
			if (sign->map_arr[i][j] == '2')
				count++;
			j++;
		}
		j = 0;
		i++;
	}
	sign->spp_count = count;
}

int	find_borders(char *str, map_cub *sign)
{
	int	i;
	int	len;
	int	flag;

	i = 0;
	len = ft_strlen(str);
	flag = 1;
	if (len == 0)
		return (0);
	while (flag)
	{
		if (str[i] == '1')
		{
			flag = 0;
			sign->mapheight++;
			if (len > sign->mapwidth)
				sign->mapwidth = len;
		}
		i++;
	}
	return (1);
}

void	init_ray1(t_trace *trace, t_ray *ray, map_cub sign)
{
	if (ray->rayDirX < 0)
	{
		trace->stepX = -1;
		trace->sideDistX = (sign.posX - trace->mapX) * trace->deltaDistX;
	}
	else
	{
		trace->stepX = 1;
		trace->sideDistX = (trace->mapX + 1.0 - sign.posX) * trace->deltaDistX;
	}
	if (ray->rayDirY < 0)
	{
		trace->stepY = -1;
		trace->sideDistY = (sign.posY - trace->mapY) * trace->deltaDistY;
	}
	else
	{
		trace->stepY = 1;
		trace->sideDistY = (trace->mapY + 1.0 - sign.posY) * trace->deltaDistY;
	}
	ray_shoot(trace, sign, ray);
}
