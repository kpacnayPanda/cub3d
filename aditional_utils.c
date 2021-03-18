/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aditional_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 15:39:58 by mrosette          #+#    #+#             */
/*   Updated: 2021/03/02 18:00:12 by mrosette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

char	*f_strjoin(char *str, char *str2)
{
	int		slen;
	int		s2len;
	int		full_len;
	char	*newstr;

	if (!str && !str2)
		return (0);
	slen = ft_strlen(str);
	s2len = ft_strlen(str2);
	full_len = slen + s2len;
	newstr = malloc(sizeof(char) * (full_len + 1));
	if (!newstr)
		return (0);
	ft_memmove(newstr, str, slen);
	ft_memmove(newstr + slen, str2, s2len);
	newstr[full_len] = '\0';
	free(str);
	return (newstr);
}

char	*copy(char *str, int start, int end)
{
	char *newstr;
	int len;
	int i;

	len = end - start + 1;
	i = 0;

	newstr = (char*)malloc((len) * sizeof(char));
	if (!newstr)
		return (NULL);

	while(len != 0 && start != end + 1)
	{
		newstr[i] = str[start];
		i++;
		start++;
	}
	newstr[i] = '\0';
	return (newstr);
}

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
