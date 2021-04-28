/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 15:56:45 by mrosette          #+#    #+#             */
/*   Updated: 2021/04/28 16:11:48 by mrosette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub.h"

void	double_check(char id, t_map_cub *sign)
{
	if (id == 'N' && sign->NO != NULL)
		error_handler(2);
	if (id == 'W' && sign->WE != NULL)
		error_handler(2);
	if (id == 'S' && sign->SO != NULL)
		error_handler(2);
	if (id == 'E' && sign->EA != NULL)
		error_handler(2);
	if (id == 'T' && sign->S != NULL)
		error_handler(2);
}

void	find_path(char *str, t_map_cub *sign, char id)
{
	int		i;
	char	*path;

	i = 0;
	while (*str != ' ')
		str++;
	double_check(id, sign);
	path = ft_strtrim(str, " ");
	if (id == 'N')
		sign->NO = path;
	if (id == 'W')
		sign->WE = path;
	if (id == 'E')
		sign->EA = path;
	if (id == 'S')
		sign->SO = path;
	if (id == 'T')
		sign->S = path;
}

void	take_color(char *str, t_map_cub *sign, char id)
{
	int		i;
	int		flag;
	char	*color;

	i = 0;
	flag = 1;
	if (id == 'F' && sign->F != NULL)
		error_handler(2);
	if (id == 'C' && sign->C != NULL)
		error_handler(2);
	while (*str != ' ')
		str++;
	color = ft_strtrim(str, " ");
	if (id == 'F')
		sign->F = color;
	if (id == 'C')
		sign->C = color;
}

int	check2(char c)
{
	if (c == 'N' || c == 'W' || c == 'E' || c == 'S')
		return (1);
	return (0);
}
