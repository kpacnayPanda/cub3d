/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 00:34:45 by mrosette          #+#    #+#             */
/*   Updated: 2021/03/19 12:01:56 by mrosette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include <math.h>

// int				key_press(int keycode, t_data *vars)
// {

// 	if (keycode == 53) //Quit the program when ESC key pressed
// 		exit(0);
// 	return (0);
// }



// void	init_st(t_data *vars)
// {
// 	vars->dirX = -1;
// 	vars->dirY = 0;
// 	vars->planeX = 0;
// 	vars->planeY = 0.66;
// 	vars->oldtime = 0;
// 	vars->time = 0;
// 	vars->CameraX = 0;
// 	vars->rayDirX = 0;
// 	vars->rayDirY = 0;
// 	//vars->sign.width = sign->width;
// 	//vars->sign.height = sign->height;
// 	//vars->sign.posX = sign->posX;
// 	//vars->sign.posY = sign->posY;
// 	//vars->sign.map_arr = sign->map_arr;
// }

int			trace(map_cub *sign)
{
    //t_data  vars;
	int i;

	i = 0;

    //init_st(&vars);
	//printf("\n %d \n", sign->width);
	//loop_main(sign);
	// vars.mlx = mlx_init();
    // vars.win = mlx_new_window(vars.mlx, 720, 480, "CUB3D");
	// mlx_hook(vars.win, 2, 0, &key_press, &vars);
	// mlx_loop_hook(vars.mlx, &loop_main, &vars);
    // mlx_loop(vars.mlx);
	return (0);
}
