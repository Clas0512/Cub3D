/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakkus <sakkus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 11:00:49 by sakkus            #+#    #+#             */
/*   Updated: 2023/07/28 11:43:10 by sakkus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_exit(int keycode, t_data *data)
{
	(void)data;
	(void)keycode;
	exit(1);
}

int	key_press(int keycode, t_data *data)
{
	if (keycode == 13)
		data->keycode[W] = 1;
	if (keycode == 1)
		data->keycode[S] = 1;
	if (keycode == 0)
		data->keycode[A] = 1;
	if (keycode == 2)
		data->keycode[D] = 1;
	if (keycode == 123)
		data->keycode[LEFT] = 1;
	if (keycode == 124)
		data->keycode[RIGHT] = 1;
	if (keycode == 53)
		ft_exit(0, NULL);
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == 13)
		data->keycode[W] = 0;
	if (keycode == 1)
		data->keycode[S] = 0;
	if (keycode == 0)
		data->keycode[A] = 0;
	if (keycode == 2)
		data->keycode[D] = 0;
	if (keycode == 123)
		data->keycode[LEFT] = 0;
	if (keycode == 124)
		data->keycode[RIGHT] = 0;
	return (0);
}

int	keyboard(t_data *data)
{
	double	move_speed;
	double	rot_speed;

	if ((data->keycode[W] || data->keycode[S])
		&& (data->keycode[A] || data->keycode[D]))
		move_speed = (0.09 / sqrt(2));
	else
		move_speed = 0.09;
	rot_speed = 0.09;
	if (data->keycode[W] && calc_move(data, 1, move_speed))
		return (0);
	else if (data->keycode[S] && calc_move(data, -1, move_speed))
		return (0);
	else if (data->keycode[A] && calc_move_d(data, -1, move_speed))
		return (0);
	else if (data->keycode[D] && calc_move_d(data, 1, move_speed))
		return (0);
	else if (data->keycode[LEFT])
		calc_rot(data, -rot_speed);
	else if (data->keycode[RIGHT])
		calc_rot(data, rot_speed);
	return (0);
}
