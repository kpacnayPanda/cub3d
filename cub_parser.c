/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 14:44:09 by mrosette          #+#    #+#             */
/*   Updated: 2021/03/19 16:14:45 by mrosette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

char	*before_newline(char *str)
{
	int		i;
	char	*newstr;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	if (!(newstr = malloc(sizeof(char) * (i + 1))))
		return (0);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		newstr[i] = str[i];
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}

char	*after_newline(char *remainder)
{
	char	*newstr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!remainder)
		return (0);
	while (remainder[i] && remainder[i] != '\n')
		i++;
	if (!remainder[i])
	{
		free(remainder);
		return (0);
	}
	if (!(newstr = malloc(sizeof(char) * ((ft_strlen(remainder) - i) + 1))))
		return (0);
	i++;
	while (remainder[i])
		newstr[j++] = remainder[i++];
	newstr[j] = '\0';
	free(remainder);
	return (newstr);
}

int        cub_parser(int fd, char **line)
{
	char		*buf;
	int			byte_read;
	static char	*remainder;

	byte_read = 1;
	if (fd < 0)
		return (-1);
	if (!(buf = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	while (!check(remainder) && byte_read != 0)
	{
		if ((byte_read = read(fd, buf, BUFFER_SIZE)) == -1)
		{
			free(buf);
			return (-1);
		}
		buf[byte_read] = '\0';
		remainder = f_strjoin(remainder, buf);
	}
	free(buf);
	*line = before_newline(remainder);
	remainder = after_newline(remainder);
	if (byte_read == 0)
		return (0);
	return (1);
}

void	ft_set_args(map_cub *sign)
{
	sign->NO = NULL;
	sign->SO = NULL;
	sign->WE = NULL;
	sign->EA = NULL;
	sign->C = NULL;
	sign->F = NULL;
	sign->S = NULL;
	sign->height = 0;
	sign->width = 0;
	sign->mapwidth = 0;
	sign->mapheight = 0;
	sign->iheight = 0;
	sign->flag = 1;
	sign->posX = -1;
	sign->posY = -1;
}

int		main()
{
	int fd;
	char *line;
	map_cub sign;
	int i;

	fd = open("map.cub", O_RDONLY);
	ft_set_args(&sign);
	while ((i = cub_parser(fd, &line)))
	{
		printf("i = %d %s\n", i, line);
		find_configs(line, &sign);
		free (line);
	}
	printf("i = %d %s\n\n", i, line);
	find_configs(line, &sign);
	free (line);
	sign.map_arr[sign.iheight] = NULL;
	int error; //del
	error = map_error_check(&sign);
	find_pos(&sign);

	//trace();

	//check contoral

	printf("width: %d\n", sign.width);
	printf("height: %d\n", sign.height);
	printf("north: %s\n", sign.NO);
	printf("south: %s\n", sign.SO);
	printf("east: %s\n", sign.EA);
	printf("west: %s\n", sign.WE);
	printf("floor: %s\n", sign.F);
	printf("ceel: %s\n", sign.C);
	printf("texture: %s\n", sign.S);
	printf("mapheight: %d\n", sign.mapheight);
	printf("mapwidth: %d\n", sign.mapwidth);
	printf("posX = %f\n", sign.posX);
	printf("posY = %f\n", sign.posY);
	int ii = 0;
	while (ii < sign.mapheight)
	{
		printf("%s\n", sign.map_arr[ii]);
		ii++;
	}
	printf("error: %d\n", error);

	// if (trace(&sign) == 2)
	// 	return (0);
	loop_main(&sign);
	return (0);
}
