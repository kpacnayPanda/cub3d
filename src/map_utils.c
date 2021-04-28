/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 18:13:11 by mrosette          #+#    #+#             */
/*   Updated: 2021/04/27 22:03:15 by mrosette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub.h"

void	free_map(map_cub *sign)
{
	int	i;

	i = 0;
	while (i < sign->mapheight)
	{
		free(sign->map_arr[i]);
		i++;
	}
	free(sign->map_arr);
}

void	free_tmp(char **tmp, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		free(tmp[i]);
		i++;
	}
	free(tmp);
}

void	check_map3(map_cub *sign, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	sign->map_arr[sign->iheight] = (char *)malloc(sizeof(char) \
				* (sign->mapwidth + 1));
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
}

void	check_map2(map_cub *sign, char *str, char **tmp)
{
	int	i;
	int	j;

	if (sign->map_arr != NULL)
		free_map(sign);
	if (!find_borders(str, sign))
		return ;
	sign->map_arr = (char **)malloc(sizeof(char *) * (sign->mapheight + 1));
	sign->flag = 0;
	i = 0;
	while (i < sign->iheight)
	{
		j = 0;
		sign->map_arr[i] = (char *)malloc(sizeof(char) * (sign->mapwidth + 1));
		while (j < sign->mapwidth && tmp[i][j] != '\0')
		{
			sign->map_arr[i][j] = tmp[i][j];
			j++;
		}
		sign->map_arr[i][j] = '\0';
		i++;
	}
	if (tmp != NULL)
		free_tmp(tmp, sign->mapheight);
	check_map3(sign, str);
}

void	check_map(char *str, map_cub *sign)
{
	int		i;
	int		j;
	char	**tmp;

	i = 0;
	j = 0;
	tmp = NULL;
	if (!sign->flag)
	{
		tmp = (char **)malloc(sizeof(char *) * (sign->mapheight + 1));
		while (i < sign->iheight)
		{
			tmp[i] = (char *)malloc(sizeof(char) * (sign->mapwidth + 1));
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
	check_map2(sign, str, tmp);
}
