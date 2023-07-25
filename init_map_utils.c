#include "cub3d.h"

int image_color(int x, int y, t_image *img)
{
	char *dst = img->buffer + (y * img->size_line + x * (img->bbp / 8));
	return (*(unsigned int*)dst);
}
void	put_cle_floo(t_data *data)
{
	int x = 0;
	while (x < data->win->width_screen)
	{
		put_image(x, 0, data->win->height_screen / 2, data->win->ceiling_color, data->screen_image);
		put_image(x, data->win->height_screen / 2, data->win->height_screen, data->win->floor_color, data->screen_image);
		x++;
	}
}

double	is_zero(double x)		
{
	if (x == 0)
		return (1e30);
	return (fabs(1 / x));
}
