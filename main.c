#include "cub3d.h"

int main(int ac, char **av)
{
	t_map	map;
	t_data	data;
	(void)ac;
	// if (ac != 2)
	// 	perror("Invalid Argument\n");
	check_main(av, &map);
	data.map = &map;
	init_data(&data);
	init_image(&data);
	init_map(&data);
	init_3d_map(&data);
	mlx_hook(data.win, 2, 1L << 0, keyboard, &data);
	mlx_hook(data.win, 17, 0, shutdown, &data);
	mlx_loop(data.mlx);
}