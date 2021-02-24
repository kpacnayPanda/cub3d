/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 15:21:06 by mrosette          #+#    #+#             */
/*   Updated: 2021/02/24 18:16:50 by mrosette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int		check(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	check_for_id(char *line)
{
	char id;

	id = '0';
	if (line[0] == 'R') //res
		id = 'R';
	if (line[0] == 'N') //north
		id = 'N';
	if (line[0] == 'W') //west
		id = 'W';
	if (line[0] == 'E') //east
		id = 'E';
	if (line[0] == 'F') //floor
		id = 'F';
	if (line[0] == 'C') //ceeling
		id = 'C';
	if (line[0] == 'S')
		id = line[1] == 'O' ? 'S' : 'T'; //south or texture sorite
	return (id);
}

// int		len_for_del_whitespaces(char *line)
// {
// 	int i;
// 	int len;

// 	i = 0;
// 	len = 0;
// 	while (line[i] != '\0')
// 	{
// 		if ((line[i] >= 48 && line[i] <= 57) || ()
// 			len++;
// 		i++;
// 	}
// 	return (len);
// }

// char	*del_whitespaces(char *line)
// {
// 	int i;
// 	int len;

// 	i = 0;
// 	len = len_for_del_whitespaces(line);
// 	while (*line)
// 	{
// 		if (*line != '0')
// 	}
// }

void	find_configs(char *line)
{
	char id;
	map_cub ids;
	char	*info;
	char	*newline;

	//newline = del_whitespaces(line);
	id = check_for_id(line);
	printf("%c\n", id);
	// if (id == 'R')
	// 	get_r_info(line, &info);

}
