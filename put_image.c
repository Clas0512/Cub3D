/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakkus <sakkus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 11:58:50 by sakkus            #+#    #+#             */
/*   Updated: 2023/07/26 17:30:43 by sakkus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(int x, int y, int color, t_image *img)
{
	char	*dst;

	dst = img->buffer + (y * img->size_line + x * (img->bbp / 8));
	*(unsigned int *)dst = color;
}

void	put_image(t_put *put, t_image *img)
{
	int	start;

	start = put->start;
	while (start < put->end)
	{
		my_mlx_pixel_put(put->x, start, put->color, img);
		start++;
	}
}
