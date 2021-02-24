/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_del_at_end.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 15:39:58 by mrosette          #+#    #+#             */
/*   Updated: 2021/02/24 18:19:31 by mrosette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

// size_t	ft_strlen(const char *s)
// {
// 	size_t	i;

// 	if (!s)
// 		return (0);
// 	i = 0;
// 	while (s[i])
// 		i++;
// 	return (i);
// }

// void	*ft_memmove(void *dst, const void *src, size_t len)
// {
// 	unsigned char *dest;
// 	unsigned char *source;

// 	dest = (unsigned char *)dst;
// 	source = (unsigned char *)src;
// 	if (!dest && !source)
// 		return (NULL);
// 	if (dest >= source)
// 	{
// 		dest = dest + len;
// 		source = source + len;
// 		while (len--)
// 		{
// 			*--dest = *--source;
// 		}
// 		return (dest);
// 	}
// 	else
// 	{
// 		while (len--)
// 			*dest++ = *source++;
// 	}
// 	return (dst);
// }

// char	*ft_strjoin(char *str, char *str2)
// {
// 	int		slen;
// 	int		s2len;
// 	int		full_len;
// 	char	*newstr;

// 	if (!str && !str2)
// 		return (0);
// 	slen = ft_strlen(str);
// 	s2len = ft_strlen(str2);
// 	full_len = slen + s2len;
// 	newstr = malloc(sizeof(char) * (full_len + 1));
// 	if (!newstr)
// 		return (0);
// 	ft_memmove(newstr, str, slen);
// 	ft_memmove(newstr + slen, str2, s2len);
// 	newstr[full_len] = '\0';
// 	free(str);
// 	return (newstr);
// }
