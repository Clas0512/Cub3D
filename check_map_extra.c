/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_extra.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakkus <sakkus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:06:57 by anargul           #+#    #+#             */
/*   Updated: 2023/07/28 12:49:15 by sakkus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_id_is_true_extra(int id, t_map *main_s)
{
	if (id == 5)
	{
		if (main_s->map_ids.f == true)
			return (1);
	}
	if (id == 6)
	{
		if (main_s->map_ids.c == true)
			return (1);
	}
	return (0);
}

int	ft_id_is_true(int id, t_map *main_s)
{
	if (id == 1)
	{
		if (main_s->map_ids.no == true)
			return (1);
	}
	else if (id == 2)
	{
		if (main_s->map_ids.so == true)
			return (1);
	}
	else if (id == 3)
	{
		if (main_s->map_ids.ea == true)
			return (1);
	}
	else if (id == 4)
	{
		if (main_s->map_ids.we == true)
			return (1);
	}
	return (ft_id_is_true_extra(id, main_s));
}

void	ft_fill_the_rgb_f(int r, int g, int b, t_map *main_s)
{
	main_s->f[0] = r;
	main_s->f[1] = g;
	main_s->f[2] = b;
	main_s->map_ids.f = true;
}

void	ft_fill_the_rgb_c(int r, int g, int b, t_map *main_s)
{
	main_s->c[0] = r;
	main_s->c[1] = g;
	main_s->c[2] = b;
	main_s->map_ids.c = true;
}

void	ft_error_2(int error, char **tmp)
{
	if (error == 2)
		printf("Id Error!\n");
	else if (error == 3)
		printf("Invalid Path Error!\n");
	else if (error == 4)
		printf("RGB Color Code Error!\n");
	ft_spec_tmp_free(tmp);
	exit(2);
}
