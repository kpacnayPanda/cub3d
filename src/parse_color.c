/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 15:24:25 by mrosette          #+#    #+#             */
/*   Updated: 2021/04/27 20:15:33 by mrosette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub.h"

int	valid_color(int r, int g, int b)
{
	if (r > 255 || g > 255 || b > 255 || r < 0 || g < 0 || b < 0)
		error_handler(6);
	return (1);
}

void	parse_color_f(t_ray *ray, char *line, map_cub *sign)
{
	int	flag;

	while (*line == ' ' || *line == ',')
		line++;
	sign->r = ft_atoi(line);
	line += ft_len(sign->r);
	if (*line != ' ' && *line != ',')
		error_handler(6);
	while (*line == ' ' || *line == ',')
		line++;
	sign->g = ft_atoi(line);
	line += ft_len(sign->g);
	if (*line != ' ' && *line != ',')
		error_handler(6);
	while (*line == ' ' || *line == ',')
		line++;
	sign->b = ft_atoi(line);
	line += ft_len(sign->b);
	if (*line != '\0')
		error_handler(6);
	flag = valid_color(sign->r, sign->g, sign->b);
	if (flag)
		sign->f = mlx_get_color_value(ray->mlx, sign->r * \
							65536 + sign->g * 256 + sign->b);
	free(sign->F);
}

void	parse_color_c(t_ray *ray, char *line, map_cub *sign)
{
	int	flag;

	while (*line == ' ' || *line == ',')
		line++;
	sign->r = ft_atoi(line);
	line += ft_len(sign->r);
	if (*line != ' ' && *line != ',')
		error_handler(6);
	while (*line == ' ' || *line == ',')
		line++;
	sign->g = ft_atoi(line);
	line += ft_len(sign->g);
	if (*line != ' ' && *line != ',')
		error_handler(6);
	while (*line == ' ' || *line == ',')
		line++;
	sign->b = ft_atoi(line);
	line += ft_len(sign->b);
	if (*line != '\0')
		error_handler(6);
	flag = valid_color(sign->r, sign->g, sign->b);
	if (flag)
		sign->c = mlx_get_color_value(ray->mlx, sign->r * 65536 \
								+ sign->g * 256 + sign->b);
	free(sign->C);
}
