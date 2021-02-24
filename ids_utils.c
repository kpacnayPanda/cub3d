/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ids_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 17:08:53 by mrosette          #+#    #+#             */
/*   Updated: 2021/02/24 18:01:55 by mrosette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int			get_r_len(char *line)
{
	int len;
	int i;

	i = 0;
	len = 0;
	while (line[i] != '\0')
	{
		if (line[i] >= 48 && line[i] <= 57)
			len++;
		i++;
	}
	return (len);
}

void		get_r_info(char *line, char **info)
{
	int	i;
	int	j;
	int	len;
	char	*buf;
	int	flag;

	i = 0;
	j = 0;
	len = get_r_len(line);
	buf = malloc(sizeof(char) * (len + 2));
	while (line[i] != '\0')
	{
		while (line[i] >= 48 && line[i] <= 57)
		{
			flag = 0;
			buf = line[i];
			i++;
		}
		if (flag == 0)
		{
			//*buf = ' ';
			flag = 1;
		}
		i++;
	}
	buf[i] = '\0';
	printf("%s\n", buf);
}
