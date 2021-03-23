/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 15:56:45 by mrosette          #+#    #+#             */
/*   Updated: 2021/03/20 17:07:27 by mrosette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub.h"

void	find_path(char *str, map_cub *sign, char id)
{
	int i;
	int flag;
	int start;
	int end;

	i = 0;
	flag = 1;

	while (str[i] && flag == 1)
	{
		if (str[i] == '.')
		{
			flag = 2;
			start = i;
		}
		i++;
	}
	end = ft_strlen(str) - 1;
	if (id == 'N')
		sign->NO = copy(str, start, end);
	if (id == 'W')
		sign->WE = copy(str, start, end);
	if (id == 'E')
		sign->EA = copy(str, start, end);
	if (id == 'S')
		sign->SO = copy(str, start, end);
	if (id == 'T')
		sign->S = copy(str, start, end);
}

void	take_color(char *str, map_cub *sign, char id)
{
	int i;
	int flag;
	int start;
	int end;

	i = 0;
	flag = 1;

	while (str[i] && flag == 1)
	{
		if (ft_isdigit(str[i]))
		{
			flag = 2;
			start = i;
		}
		i++;
	}
	end = ft_strlen(str) - 1;
	if (id == 'F')
		sign->F = copy(str, start, end);
	if (id == 'C')
		sign->C = copy(str, start, end);
}
