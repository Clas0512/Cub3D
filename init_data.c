/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakkus <sakkus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 11:38:40 by sakkus            #+#    #+#             */
/*   Updated: 2023/07/28 11:06:07 by sakkus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_win(t_win *win, t_map *map, void *mlx)
{
	win->ceiling_color = map->crgb;
	win->floor_color = map->frgb;
	win->height_screen = 960;
	win->width_screen = 1280;
	win->win_addres = mlx_new_window(mlx, win->width_screen,
			win->height_screen, "cub3d");
}

void	init_player(t_player *player, t_map	*map)
{
	player->pos_x = (double)map->p_x + 0.5;
	player->pos_y = (double)map->p_y + 0.5;
	if (map->original_map[(int)player->pos_y][(int)player->pos_x] == 1)
		player->pos_x -= 0.5;
	player->direction = map->player_direction;
	get_dir(player);
	player->speed = 0.006000;
}

void	init_image(t_image *img, void *mlx, t_win *win)
{
	img->img_adress = mlx_new_image(mlx, win->width_screen,
			win->height_screen);
	img->buffer = mlx_get_data_addr(img->img_adress, &(img->bbp),
			&(img->size_line), &(img->endian));
}

void	init_walls(t_image *walls, t_map *map, void *mlx)
{
	walls[NORTH].img_adress = mlx_xpm_file_to_image(mlx, map->no,
			&(walls[NORTH].width), &(walls[NORTH].height));
	walls[SOUTH].img_adress = mlx_xpm_file_to_image(mlx, map->so,
			&(walls[SOUTH].width), &(walls[SOUTH].height));
	walls[EAST].img_adress = mlx_xpm_file_to_image(mlx, map->ea,
			&(walls[EAST].width), &(walls[EAST].height));
	walls[WEST].img_adress = mlx_xpm_file_to_image(mlx, map->we,
			&(walls[WEST].width), &(walls[WEST].height));
	walls[NORTH].buffer = mlx_get_data_addr(walls[NORTH].img_adress,
			&(walls[NORTH].bbp), &(walls[NORTH].size_line),
			&(walls[NORTH].endian));
	walls[SOUTH].buffer = mlx_get_data_addr(walls[SOUTH].img_adress,
			&(walls[SOUTH].bbp), &(walls[SOUTH].size_line),
			&(walls[SOUTH].endian));
	walls[EAST].buffer = mlx_get_data_addr(walls[EAST].img_adress,
			&(walls[EAST].bbp), &(walls[EAST].size_line),
			&(walls[EAST].endian));
	walls[WEST].buffer = mlx_get_data_addr(walls[WEST].img_adress,
			&(walls[WEST].bbp), &(walls[WEST].size_line),
			&(walls[WEST].endian));
}

void	init_data(t_map *map, t_data *data)
{
	t_win		*win;
	t_player	*player;
	t_image		*screen_image;
	t_image		*walls;
	int			i;

	data->mlx = mlx_init();
	walls = malloc(sizeof(t_image) * 4);
	player = malloc(sizeof(t_player));
	screen_image = malloc(sizeof(t_image));
	win = malloc(sizeof(t_win));
	init_win(win, map, data->mlx);
	init_player(player, map);
	init_image(screen_image, data->mlx, win);
	init_walls(walls, map, data->mlx);
	data->player = player;
	data->win = win;
	data->screen_image = screen_image;
	data->walls = walls;
	data->map = map->original_map;
	data->x_len = map->map_infos.x;
	data->y_len = map->map_infos.y;
	i = 0;
	while (i < 6)
		data->keycode[i++] = 0;
}
