#include "cub3d.h"

int shutdown(void *s_data)
{
	(void)s_data;
	printf("Pencerenin çarpi(x) tuşuna basildi.\n");
	exit(0);
}

int keyboard(int keycode, t_data *data)
{
	int x = data->player->p_x;
	int y = data->player->p_y;
	if (keycode == 119 || keycode == 13){
		printf("W tuşuna basildi.\n");
		x += (int)(data->player->p_delta_x*10);
		y += (int)(data->player->p_delta_y*10);
		printf("ok\n");
	}
	else if (keycode == 115 || keycode == 1){
		printf("S tuşuna basildi.\n");
		x -= (int)(data->player->p_delta_x*10);
		y -= (int)(data->player->p_delta_y*10);
	}
	else if (keycode == 100 || keycode == 2 || keycode == 65363 || keycode == 124){
		printf("D tuşuna basildi.\n");
		data->player->alpha += 0.1;
		if (data->player->alpha > 2*PI){
			data->player->alpha -= 2*PI;
		}
		data->player->p_delta_x = cos(data->player->alpha);
		data->player->p_delta_y = sin(data->player->alpha);
	}
	else if (keycode == 97 || keycode == 0 || keycode == 65361 || keycode == 123){
		printf("A tuşuna basildi.\n");
		data->player->alpha -= 0.1;
		if (data->player->alpha < 0){
			data->player->alpha += 2*PI;
		}
		data->player->p_delta_x = cos(data->player->alpha);
		data->player->p_delta_y = sin(data->player->alpha);
	}
	else if (keycode == 53 || keycode == 65307){
		printf("ESC tuşuna basildi.\n");
		shutdown(&data);
	}
	if (data->map->original_map[y / data->units][x / data->units] == '1')
		return (0);
	data->player->p_x = x;
	data->player->p_y = y;
	init_map(data);
	return (0);
}