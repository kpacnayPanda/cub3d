/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 15:24:25 by mrosette          #+#    #+#             */
/*   Updated: 2021/03/24 17:31:31 by mrosette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub.h"

void	parse_color_f(t_ray *ray, char *line, map_cub *sign)
{
	int r;
	int g;
	int b;

	//line++;
	while (*line == ' ' || *line == ',')
		line++;
	r = ft_atoi(line);
	line += ft_len(r);
	// if (*line != ' ' && *line != ',')
	// 	ft_error(10);
	while (*line == ' ' || *line == ',')
		line++;
	g = ft_atoi(line);
	line += ft_len(g);
	// if (*line != ' ' && *line != ',')
	// 	ft_error(10);
	while (*line == ' ' || *line == ',')
		line++;
	b = ft_atoi(line);
	line += ft_len(b);
	// if (*line != '\0')
	// 	ft_error(10);
	sign->f = mlx_get_color_value(ray->mlx, r * 65536 + g * 256 + b);
}

void	parse_color_c(t_ray *ray, char *line, map_cub *sign)
{
	int r;
	int g;
	int b;

	//line++;
	while (*line == ' ' || *line == ',')
		line++;
	r = ft_atoi(line);
	line += ft_len(r);
	// if (*line != ' ' && *line != ',')
	// 	ft_error(10);
	while (*line == ' ' || *line == ',')
		line++;
	g = ft_atoi(line);
	line += ft_len(g);
	// if (*line != ' ' && *line != ',')
	// 	ft_error(10);
	while (*line == ' ' || *line == ',')
		line++;
	b = ft_atoi(line);
	line += ft_len(b);
	// if (*line != '\0')
	// 	ft_error(10);
	sign->c = mlx_get_color_value(ray->mlx, r * 65536 + g * 256 + b);
}

