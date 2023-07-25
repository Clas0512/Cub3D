/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakkus <sakkus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 11:55:33 by sakkus            #+#    #+#             */
/*   Updated: 2023/07/25 19:09:25 by sakkus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	calc_move(t_data *data, int sign, double move_speed)
{
	double	x;
	double	y;

	x = data->player->pos_x;
	y = data->player->pos_y;
	if (sign == 1)
	{
		x += data->player->dir_x * move_speed;
		y += data->player->dir_y * move_speed;
	}
	else
	{
		x -= data->player->dir_x * move_speed;
		y -= data->player->dir_y * move_speed;
	}
	if (data->map[(int)y][(int)x] == '1')
	{
		return (1);
	}
	data->player->pos_x = x;
	data->player->pos_y = y;
	return (0);
}

void	calc_rot(t_data *data, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->player->dir_x;
	old_plane_x = data->player->plane_x;
	data->player->dir_x = data->player->dir_x * cos(rot_speed)
		- data->player->dir_y * sin(rot_speed);
	data->player->dir_y = old_dir_x * sin(rot_speed)
		+ data->player->dir_y * cos(rot_speed);
	data->player->plane_x = data->player->plane_x * cos(rot_speed)
		- data->player->plane_y * sin(rot_speed);
	data->player->plane_y = old_plane_x * sin(rot_speed)
		+ data->player->plane_y * cos(rot_speed);
}

int	calc_move_d(t_data *data, int sign, double move_speed)
{
	double	x;
	double	y;

	if (sign == 1)
	{
		x = data->player->pos_x + data->player->plane_x * move_speed;
		y = data->player->pos_y + data->player->plane_y * move_speed;
	}
	else
	{
		x = data->player->pos_x - data->player->plane_x * move_speed;
		y = data->player->pos_y - data->player->plane_y * move_speed;
	}
	if (data->map[(int)y][(int)x] == '1')
		return (1);
	data->player->pos_x = x;
	data->player->pos_y = y;
	return (0);
}

int	keyboard(int keycode, t_data *data)
{
	double	move_speed;
	double	rot_speed;

	move_speed = data->player->speed * 20.0;
	rot_speed = data->player->speed * 10.0;
	if (keycode == 13 && calc_move(data, 1, move_speed))
		return (0);
	else if (keycode == 1 && calc_move(data, -1, move_speed))
		return (0);
	else if (keycode == 0 && calc_move_d(data, -1, move_speed))
		return (0);
	else if (keycode == 2 && calc_move_d(data, 1, move_speed))
		return (0);
	else if (keycode == 123)
		calc_rot(data, rot_speed);
	else if (keycode == 124)
		calc_rot(data, -rot_speed);
	init_map(data);
	return (0);
}

int	main(int ac, char *arv[])
{
	t_data	data;
	t_map	map;

	(void)ac;
	check_main(arv, &map);
	init_data(&map, &data);
	init_map(&data);
	mlx_hook(data.win->win_addres, 2, 0, keyboard, &data);
	mlx_loop(data.mlx);
	return (0);
}
