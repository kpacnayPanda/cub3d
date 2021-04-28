/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 14:14:23 by mrosette          #+#    #+#             */
/*   Updated: 2021/04/28 16:58:55 by mrosette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub.h"

int	check_util(t_map_cub *sign, int i, int j)
{
	if (i == 0 || j == sign->mapwidth - 1 || i == sign->mapheight - 1 || \
		sign->mapwidth == 0)
		return (0);
	if (sign->map_arr[i + 1][j] == ' ' || sign->map_arr[i][j + 1] == ' ')
		return (0);
	if (sign->map_arr[i - 1][j] == ' ' || sign->map_arr[i][j - 1] == ' ')
		return (0);
	return (1);
}

int	map_error_check(t_map_cub *sign, int j)
{
	int	i;

	i = -1;
	while (++i < sign->mapheight)
	{
		j = 0;
		while (j < sign->mapwidth && sign->map_arr[i][j] != '\0')
		{
			if (sign->map_arr[i][j] == '0' || sign->map_arr[i][j] == '2' \
			|| sign->map_arr[i][j] == 'N' || sign->map_arr[i][j] == 'W' \
			|| sign->map_arr[i][j] == 'E' || sign->map_arr[i][j] == 'S' \
			|| sign->map_arr[i][j] == '1' || sign->map_arr[i][j] == ' ')
			{
				if (sign->map_arr[i][j] != '1' && sign->map_arr[i][j] != ' ')
				{
					if (!check_util(sign, i, j))
						return (0);
				}
			}
			else
				error_handler(3);
			j++;
		}
	}
	return (1);
}

void	find_pos(t_map_cub *sign, int flag)
{
	int	i;
	int	j;

	i = 0;
	while (i < sign->mapheight)
	{
		j = 0;
		while (j < sign->mapwidth)
		{
			if (sign->map_arr[i][j] == 'N' || sign->map_arr[i][j] == 'S' || \
			sign->map_arr[i][j] == 'W' || sign->map_arr[i][j] == 'E')
			{
				if (flag == 1)
					error_handler(3);
				sign->posX = j + 0.5;
				sign->posY = i + 0.5;
				flag = 1;
				sign->player = sign->map_arr[i][j];
			}
			j++;
		}
		i++;
	}
	return ;
}
