/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 14:14:23 by mrosette          #+#    #+#             */
/*   Updated: 2021/03/19 11:05:30 by mrosette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int		check_util(map_cub *sign, int i, int j)
{
	if (i == 0 || j == sign->mapwidth - 1 || i == sign->mapheight - 1 ||
		sign->mapwidth == 0)
		return (0);

	if (sign->map_arr[i + 1][j] == ' ' || sign->map_arr[i][j + 1] == ' ')
		return (0);
	if (sign->map_arr[i - 1][j] == ' ' || sign->map_arr[i][j - 1] == ' ')
		return (0);
	return (1);
}

int		map_error_check(map_cub *sign)
{
	int i;
	int j;

	i = 0;
	j = 0;

	while (i < sign->mapheight)
	{
		while (j < sign->mapwidth && sign->map_arr[i][j] != '\0')
		{
			if (sign->map_arr[i][j] == '0' || sign->map_arr[i][j] == '2')
			{
				if (!check_util(sign, i, j))
					return (0);
			}
			j++;
		}
		i++;
		j = 0;
	}
	return (1);
}

void	find_pos(map_cub *sign)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < sign->mapheight)
	{
		while(j < sign->mapwidth)
		{
			if (sign->map_arr[i][j] == 'N'|| sign->map_arr[i][j] == 'S' ||
			sign->map_arr[i][j] == 'W' || sign->map_arr[i][j] == 'E')
			{
				sign->posX = i;
				sign->posY = j;
				return;
			}
			j++;
		}
		i++;
		j = 0;
	}
}
