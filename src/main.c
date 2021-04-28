/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 14:44:09 by mrosette          #+#    #+#             */
/*   Updated: 2021/04/28 17:11:12 by mrosette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub.h"

int	parse_file(t_map_cub *sign, char *str, int fd)
{
	int		i;
	char	*line;
	int		flag;

	i = 0;
	line = NULL;
	flag = 0;
	i = cub_parser(fd, &line, 1, 0);
	while (i)
	{
		flag = find_configs(line, sign);
		free(line);
		if (flag == 1)
			break ;
		i = cub_parser(fd, &line, 1, 0);
	}
	if (flag != 1)
	{
		find_configs(line, sign);
		free(line);
	}
	sign->map_arr[sign->iheight] = NULL;
	if (!map_error_check(sign, 0))
		error_handler(3);
	return (1);
}

int	cub_start(char *str, t_ray *ray)
{
	t_map_cub	sign;
	t_key		key;
	t_trace		trace;
	int			fd;

	ft_set_args(&sign);
	ft_set_keys(&key);
	fd = open(str, O_RDONLY);
	if (fd < 0)
		error_handler(4);
	if (parse_file(&sign, str, fd))
	{
		find_pos(&sign, 0);
		check_for_valid(&sign);
		find_sprites(&sign);
		sign.map_arr[(int)sign.posY][(int)sign.posX] = '0';
		init_st(ray, &sign, &key, &trace);
		init_sprite(ray, 0);
	}
	return (0);
}

void	start(char *str)
{
	t_ray	ray;
	t_spvar	svar;
	t_img	img;

	cub_start(str, &ray);
	ft_set_spvars(&ray, &svar, &img);
	loop_main(&ray);
}

int	main(int argc, char **argv)
{
	if (argc == 2 && ft_strnstr(argv[1], ".cub", ft_strlen(argv[1])))
		start(argv[1]);
	else
	{
		if (argc == 3 && (ft_strncmp(argv[2], "--save", 6) == 0))
			bmp(argv[1]);
		else
			error_handler(1);
	}
	return (0);
}
