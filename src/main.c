/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 14:44:09 by mrosette          #+#    #+#             */
/*   Updated: 2021/04/10 17:39:22 by mrosette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub.h"

int		parse_file(map_cub *sign, char *str)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	line = NULL;
	fd = open(str, O_RDONLY);
	if (fd == -1)
		error_handler(4);
	while ((i = cub_parser(fd, &line)))
	{
		printf("i = %d %s\n", i, line);
		find_configs(line, sign);
		free(line);
	}
	printf("i = %d %s\n\n", i, line);
	find_configs(line, sign);
	free(line);
	sign->map_arr[sign->iheight] = NULL;
	if (!map_error_check(sign))
		return (0);
	return (1);
}

int		cub_start(char *str)
{
	map_cub	sign;
	t_key	key;
	t_ray	ray;
	t_trace	trace;
	int ii = 0; //del

	ft_set_args(&sign);
	ft_set_keys(&key);
	ft_set_trace(&trace);
	if (parse_file(&sign, str))
	{
		find_pos(&sign);
		check_for_valid(&sign);
		//find_sprites(&sign);

		//check control
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
		while (ii < sign.mapheight)
		{
			printf("%s\n", sign.map_arr[ii]);
			ii++;
		}
		sign.map_arr[(int)sign.posX][(int)sign.posY] = '0';
		init_st(&ray, &sign, &key, &trace);
		loop_main(&ray);
	}
	return (0);
}

int		main(int argc, char **argv)
{
	if (argc == 2 && ft_strnstr(argv[1], ".cub", ft_strlen(argv[1])))
		cub_start(argv[1]);
	else
	{
		if (argc == 3 && (ft_strncmp(argv[2], "--save", 6) == 0))
			printf("MAKE MAP PIC");
		else
			error_handler(1);
	}
	return (0);
}
