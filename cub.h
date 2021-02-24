/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 14:36:09 by mrosette          #+#    #+#             */
/*   Updated: 2021/02/24 18:31:17 by mrosette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "libft/libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h> //del

typedef struct s_stuct
{
    int width;
    int height;
    char *NO;
    char *SO;
    char *WE;
    char *EA;

    char *S;
    char *F;
    char *C;

    int facing;

}               map_cub;

# define BUFFER_SIZE 128

int		check(char *str);
int		cub_parser(int fd, char **line);
void	find_configs(char *line);
void	get_r_info(char *line, char **info);
// size_t	ft_strlen(const char *s); //del
// char	*ft_strjoin(char *str, char *str2); //del

#endif
