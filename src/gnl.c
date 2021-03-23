/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 16:10:06 by mrosette          #+#    #+#             */
/*   Updated: 2021/03/23 16:10:23 by mrosette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub.h"

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
