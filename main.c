/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakkus <sakkus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 11:55:33 by sakkus            #+#    #+#             */
/*   Updated: 2023/07/28 15:40:29 by sakkus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	loop(t_data *data)
{
	keyboard(data);
	init_map(data);
	return (0);
}

int	main(int ac, char *arv[])
{
	t_data	data;
	t_map	map;

	if (ac != 2)
	{
		printf("Missing Arguments !\n");
		return (0);
	}
	check_main(arv, &map);
	init_data(&map, &data);
	init_map(&data);
	mlx_hook(data.win->win_addres, 2, 0, key_press, &data);
	mlx_hook(data.win->win_addres, 3, 0, key_release, &data);
	mlx_hook(data.win->win_addres, 17, 1L << 2, ft_exit, NULL);
	mlx_loop_hook(data.mlx, loop, &data);
	mlx_loop(data.mlx);
	return (0);
}
