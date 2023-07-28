/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakkus <sakkus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 11:44:21 by sakkus            #+#    #+#             */
/*   Updated: 2023/07/28 11:14:58 by sakkus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	image_color(int x, int y, t_image *img)
{
	char	*dst;

	dst = img->buffer + (y * img->size_line + x * (img->bbp / 8));
	return (*(unsigned int *)dst);
}

void	put_cle_floo(t_data *data)
{
	t_put	put_c;
	t_put	put_f;

	put_c = (t_put){.color = data->win->ceiling_color, .start = 0,
		.end = data->win->height_screen / 2 + 100, .x = 0};
	put_f = (t_put){.color = data->win->floor_color,
		.start = data->win->height_screen / 2 + 100,
		.end = data->win->height_screen, .x = 0};
	while (put_c.x < data->win->width_screen)
	{
		put_image(&put_c, data->screen_image);
		put_image(&put_f, data->screen_image);
		put_c.x++;
		put_f.x++;
	}
}

double	is_zero(double x)
{
	if (x == 0)
		return (1e30);
	return (fabs(1 / x));
}

t_put	new_struct(int color, int x, int start, int end)
{
	t_put	res;

	res = (t_put){.color = color, .start = start, .end = end, .x = x};
	return (res);
}
