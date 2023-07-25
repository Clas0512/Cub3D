/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakkus <sakkus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 12:02:29 by sakkus            #+#    #+#             */
/*   Updated: 2023/07/25 12:03:32 by sakkus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_ray(int x, t_data *data, t_ray *ray)
{
	ray->camera_x = 2 * x / (double)data->win->width_screen - 1;
	ray->ray_dir_x = data->player->dir_x + data->player->plane_x
		* ray->camera_x;
	ray->ray_dir_y = data->player->dir_y + data->player->plane_y
		* ray->camera_x;
	ray->map_x = (int)data->player->pos_x;
	ray->map_y = (int)data->player->pos_y;
	ray->delta_dist_x = is_zero(ray->ray_dir_x);
	ray->delta_dist_y = is_zero(ray->ray_dir_y);
	ray->hit = 0;
	ray->pitch = 100;
}

void	step_calc(t_player *player, t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->pos_x - ray->map_x)
			* ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - player->pos_x)
			* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->pos_y - ray->map_y)
			* ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - player->pos_y)
			* ray->delta_dist_y;
	}
}

void	dda(t_ray *ray, char **map)
{
	while (1)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (map[ray->map_y][ray->map_x] == '1')
			break ;
	}
}

void	start_end_calc(t_ray *ray, int height)
{
	ray->draw_start = -ray->line_height / 2 + height / 2; 
	ray->draw_end = ray->line_height / 2 + height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	if (ray->draw_end >= height)
		ray->draw_end = height - 1;
}
