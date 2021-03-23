/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 18:13:11 by mrosette          #+#    #+#             */
/*   Updated: 2021/03/20 17:07:19 by mrosette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub.h"

int		find_borders(char *str, map_cub *sign)
{
	int i;
	int len;
	int flag;

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

void	set_map_arr(map_cub *sign)
{
	sign->map_arr = (char**)malloc(sizeof(char*) * (sign->mapheight + 1));
	sign->flag = 0;
}

void	check_map(char *str, map_cub *sign)
{
	int i;
	int j;
	char **tmp;

	i = 0;
	j = 0;
	// tmp = NULL;
	if (!sign->flag)
	{
		tmp = (char**)malloc(sizeof(char*) * (sign->mapheight + 1));
		while (i < sign->iheight)
		{
			tmp[i] = (char*)malloc(sizeof(char) * (sign->mapwidth + 1));
			while (j < sign->mapwidth && sign->map_arr[i][j] != '\0')
			{
				tmp[i][j] = sign->map_arr[i][j];
				j++;
			}
			tmp[i][j] = '\0';
			i++;
			j = 0;
		}
		tmp[i] = NULL;
	}
	//free(sign->map_arr);
	i = 0;
	j = 0;

	if (!find_borders(str, sign))
		return;
	set_map_arr(sign);
	while (i < sign->iheight)
	{
 		sign->map_arr[i] = (char*)malloc(sizeof(char) * (sign->mapwidth + 1));
		while (j < sign->mapwidth && tmp[i][j] != '\0')
		{
			sign->map_arr[i][j] = tmp[i][j];
			j++;
		}

		sign->map_arr[i][j] = '\0';
		i++;
		j = 0;
	}

	 i = 0;
	 j = 0;
	sign->map_arr[sign->iheight] = (char*)malloc(sizeof(char) * (sign->mapwidth + 1));
	while (j < sign->mapwidth && str[i] != '\0')
	{
		sign->map_arr[sign->iheight][j] = str[i];
		j++;
		i++;
	}
	while (j < sign->mapwidth)
	{
		sign->map_arr[sign->iheight][j] = ' ';
		j++;
	}
	sign->map_arr[sign->iheight][j] = '\0';
	sign->iheight++;
	//free(tmp);
}
