/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakkus <sakkus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 11:38:19 by sakkus            #+#    #+#             */
/*   Updated: 2023/07/25 11:38:20 by sakkus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	ft_rgb_convert(t_map *map)
{
	map->frgb = create_trgb(0, map->f[0], map->f[1], map->f[2]);
	map->crgb = create_trgb(0, map->c[0], map->c[1], map->c[2]);
}
