#include "cub3d.h"

void	init_image(t_data *data)
{
	data->wall_imgs = malloc(sizeof(t_data *) * 4);
	data->wall_imgs[NORTH].image = mlx_xpm_file_to_image(data->mlx, data->map->no, &(data->wall_imgs[NORTH].width),
		&(data->wall_imgs[NORTH].height));
	data->wall_imgs[SOUTH].image = mlx_xpm_file_to_image(data->mlx, data->map->no, &(data->wall_imgs[SOUTH].width),
		&(data->wall_imgs[SOUTH].height));
	printf("%p\n", data->wall_imgs[NORTH].buffer);
	data->wall_imgs[EAST].image = mlx_xpm_file_to_image(data->mlx, data->map->no, &(data->wall_imgs[EAST].width),
		&(data->wall_imgs[EAST].height));
	data->wall_imgs[WEST].image = mlx_xpm_file_to_image(data->mlx, data->map->no, &(data->wall_imgs[WEST].width),
		&(data->wall_imgs[WEST].height));
	// data->wall_imgs[NORTH].buffer = mlx_get_data_addr(data->wall_imgs[NORTH].image,
	// 	&(data->wall_imgs[NORTH].bits_per_pixel), &(data->wall_imgs[NORTH].size_line), &(data->wall_imgs[NORTH].endian));
	// data->wall_imgs[SOUTH].buffer = mlx_get_data_addr(data->wall_imgs[SOUTH].image,
	// 	&(data->wall_imgs[SOUTH].bits_per_pixel), &(data->wall_imgs[SOUTH].size_line), &(data->wall_imgs[SOUTH].endian));
	// data->wall_imgs[EAST].buffer = mlx_get_data_addr(data->wall_imgs[EAST].image,
	// 	&(data->wall_imgs[EAST].bits_per_pixel), &(data->wall_imgs[EAST].size_line), &(data->wall_imgs[EAST].endian));
	// data->wall_imgs[WEST].buffer = mlx_get_data_addr(data->wall_imgs[WEST].image,
	// 	&(data->wall_imgs[WEST].bits_per_pixel), &(data->wall_imgs[WEST].size_line), &(data->wall_imgs[WEST].endian));
}

void	init_data(t_data *data)
{
	data->units = 64;
	data->height = data->map->map_infos.y * data->units;
	data->width = data->map->map_infos.x * data->units;
	data->player = &data->map->player;
	data->player->p_x *= data->units;
	data->player->p_y *= data->units;
	data->player->alpha = 2 * PI;
	data->player->p_delta_x = cos(data->player->alpha);
	data->player->p_delta_y = sin(data->player->alpha);
	data->raycast = malloc(sizeof(int *) * data->width);
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->width * 2, data->height, "Cub3d");
	data->win_img_2d = malloc(sizeof(t_image));
	data->win_img_3d = malloc(sizeof(t_image));
	data->win_img_2d->image = mlx_new_image(data->mlx, data->width, data->height);
	data->win_img_3d->image = mlx_new_image(data->mlx, data->width, data->height);
	data->win_img_2d->buffer = mlx_get_data_addr(data->win_img_2d->image, &(data->win_img_2d->bits_per_pixel), &(data->win_img_2d->size_line), &(data->win_img_2d->endian));
	data->win_img_3d->buffer = mlx_get_data_addr(data->win_img_3d->image, &(data->win_img_3d->bits_per_pixel), &(data->win_img_3d->size_line), &(data->win_img_3d->endian));
	data->win_img_2d->width = data->width;
	data->win_img_2d->height = data->height;
	data->win_img_3d->width = data->width;
	data->win_img_3d->height = data->height;
}