#include "cub3d.h"

void my_mlx_pixel_put(int x, int y, int color, t_image *img){
	char *dst = img->buffer + (y * img->size_line + x * (img->bbp / 8));
	*(unsigned int*)dst = color;
}

void	put_image(int x, int start, int end, int color, t_image *img)
{
	while (start < end)
    {
        my_mlx_pixel_put(x, start, color, img);
        start++;
    }  
}