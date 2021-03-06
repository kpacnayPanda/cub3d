/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   id_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 15:21:06 by mrosette          #+#    #+#             */
/*   Updated: 2021/04/28 17:01:43 by mrosette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub.h"

int	check_blank(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (len == 0)
		return (1);
	return (0);
}

char	check_for_id(char *line, char id)
{
	int		i;
	int		flag;

	i = 0;
	while (!ft_isalpha(line[i]) && line[i] != '\0')
		i++;
	if (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
		id = 'S';
	if (line[i] == 'S' && line[i + 1] == ' ')
		id = 'T';
	if (line[i] == 'R' && line[i + 1] == ' ')
		id = line[i];
	if (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
		id = 'E';
	if (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
		id = 'W';
	if ((line[i] == 'F' || line[i] == 'C') && line[i + 1] == ' ')
		id = line[i];
	if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
		id = 'N';
	flag = check_blank(line);
	if (flag)
		id = '2';
	return (id);
}

int	find_configs(char *line, t_map_cub *sign)
{
	char	id;

	id = check_for_id(line, '0');
	if (id == 'R')
		take_r_specs(line, sign, 0);
	if (id == 'F' || id == 'C')
		take_color(line, sign, id);
	if (id == 'S' || id == 'N' || id == 'W' || id == 'E' || id == 'T')
		find_path(line, sign, id);
	if (id == '2' && sign->map_arr != NULL)
		return (1);
	if (id == '0')
	{
		check_before_map(sign, line);
		check_map(line, sign);
	}
	return (0);
}
