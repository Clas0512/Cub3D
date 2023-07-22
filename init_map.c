#include "cub3d.h"


void my_mlx_pixel_put(int x, int y, int color, t_image *img){
	char *dst = img->buffer + (y * img->size_line + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	put_2d(int begin_x, int begin_y, int end_x, int end_y, int color,t_image *img)
{
	int	x;

	while (begin_y < end_y)
	{
		x = begin_x;
		while (x < end_x)
			my_mlx_pixel_put(x++, begin_y, color, img);
		begin_y++;
	}
}

void	init_map(t_data *data)
{
	int	x;
	int	y;

	mlx_clear_window(data->mlx, data->win);
	y = 0;
	printf("px:%d, py:%d\n", data->player->p_x, data->player->p_y);
	while (data->map->original_map[y])
	{
		x = 0;
		while (data->map->original_map[y][x])
		{
			if (data->map->original_map[y][x] == '1')
				put_2d(x * data->units, y * data->units, (x * data->units) + data->units, (y * data->units) + data->units, data->map->crgb, data->win_img_2d);
			else
				put_2d(x * data->units, y * data->units, (x * data->units) + data->units, (y * data->units) + data->units, data->map->frgb, data->win_img_2d);
			x++;
		}
		y++;
	}
	init_raycast(data);
	init_3d_map(data);
	mlx_put_image_to_window(data->mlx, data->win, data->win_img_2d->image, 0, 0);
}

void DDA(int X0, int Y0, int X1, int Y1, int color, t_image *img)
{
    // calculate dx & dy
    int dx = X1 - X0;
    int dy = Y1 - Y0;
 
    // calculate steps required for generating pixels
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
 
    // calculate increment in x & y for each steps
    float Xinc = dx / (float)steps;
    float Yinc = dy / (float)steps;
 
    // Put pixel for each step
    float X = X0;
    float Y = Y0;
    for (int i = 0; i <= steps; i++) {
        my_mlx_pixel_put(round(X), round(Y),
                 color, img); // put pixel at (X,Y)
        X += Xinc; // increment in x at each step
        Y += Yinc; // increment in y at each step
                    // generation step by step
    }
}

void	init_raycast(t_data *data)
{
	float	end_x;
	float	end_y;
	int		i = 0;
	int		k = 1;
	float	alpha;
	float	dx;
	float	dy;
	

	alpha = data->player->alpha - (RADIAN * 66.0f / 2);
	dx = data->player->p_delta_x;
	dy = data->player->p_delta_y;
	if (alpha < 0)
		alpha += 2 * PI;
	printf("dx:%f, dy:%f\n", dx, dy);
	while (i < data->width)
	{
		k = 0;
		end_x = (data->player->p_x) + data->player->p_delta_x;
		end_y = (data->player->p_y) + data->player->p_delta_y;
		while (k < 10000)
		{
			end_x += dx;
			end_y += dy;
			if (data->map->original_map[(int)(end_y) / data->units][(int)(end_x) / data->units] == '1')
				break;
			k++;
		}
		DDA(data->player->p_x, data->player->p_y, end_x, end_y, GREEN, data->win_img_2d);
		data->raycast[i] = sqrt(pow(end_x - data->player->p_x, 2) + pow(end_y - data->player->p_y, 2));
		alpha += RADIAN * 66.0f / ((float)data->width);
		dx = cos(alpha);
		dy = sin(alpha);
		i++;
	}
}

int	calc_wall_height(int ray_len, int data_height)
{
	if ((58 * data_height / ray_len) >= data_height)
		return (data_height);
	return (58 * data_height / ray_len);
}

// int	set_wall_color()
// {
// 	int color;
// 	return (color);
// }

void	init_3d_map(t_data *data)
{
	// int color;
	int wall_len;
	put_2d(0, 0, data->width - 1, data->height / 2, data->map->crgb, data->win_img_3d);
	put_2d(0, data->height / 2, data->width - 1, data->height - 1, data->map->frgb, data->win_img_3d);
	int i;

	i = 0;
	while (i < data->width)
	{
		wall_len = calc_wall_height(data->raycast[i], data->height);
		// color = set_wall_color(data->raycast[i]);
		put_2d(0 + i, data->height / 2 - wall_len / 2, 0 + i + 1, data->height / 2 + wall_len / 2, PURPLE, data->win_img_3d);
		i++;
	}
	
	mlx_put_image_to_window(data->mlx, data->win, data->win_img_3d->image, data->width, 0);
}
