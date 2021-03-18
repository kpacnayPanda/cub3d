/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 17:08:53 by mrosette          #+#    #+#             */
/*   Updated: 2021/03/02 17:46:03 by mrosette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	take_width_r(char *str, int flag, map_cub *sign)
{
	int i;
	int widthlen;
	char *tmp;
	int num;

	widthlen = 0;
	i = 0;
	num = 0;

	while (str[i] != ' ' && str[i] != '\0')
	{
		widthlen++;
		i++;
	}

	tmp = (char*)malloc((widthlen + 1) * sizeof(char));
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
}


void	take_r_specs(char *str, map_cub *sign)
{
	int i;
	int flag;

	i = 0;
	flag = 0;

	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) && (flag == 0))
		{
			take_width_r(&str[i], flag, sign);
			flag = 1;
		}
		if (ft_isdigit(str[i]) && (flag == 2))
		{
			take_width_r(&str[i], flag, sign);
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
