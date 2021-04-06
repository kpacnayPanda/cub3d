/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   id_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 15:21:06 by mrosette          #+#    #+#             */
/*   Updated: 2021/04/06 14:28:50 by mrosette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub.h"

char	check_for_id(char *line)
{
	char	id;
	int		i;

	i = 0;
	while (!ft_isalpha(line[i]) && line[i] != '\0')
		i++;
	id = '0';
	if (line[i] == 'S' && line[i + 1] == 'O')
		id = 'S';
	if (line[i] == 'S' && line[i + 1] != 'O')
		id = 'T';
	if (line[i] == 'W' || line[i] == 'E' || line[i] == 'R')
		id = line[i];
	if (line[i] == 'F' || line[i] == 'C')
		id = line[i];
	if (line[i] == 'N' && line[i + 1] == 'O')
		id = 'N';
	return (id);
}

void	find_configs(char *line, map_cub *sign)
{
	char	id;

	id = check_for_id(line);
	printf("%c\n", id);
	if (id == 'R')
		take_r_specs(line, sign);
	if (id == 'F' || id == 'C')
		take_color(line, sign, id);
	if (id == 'S' || id == 'N' || id == 'W' || id == 'E' || id == 'T')
		find_path(line, sign, id);
	if (id == '0')
		check_map(line, sign);
}
