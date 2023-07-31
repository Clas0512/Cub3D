/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anargul <anargul@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 16:58:16 by anargul           #+#    #+#             */
/*   Updated: 2023/07/31 12:39:35 by anargul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init(t_map *main_s)
{
	main_s->map_ids.no = false;
	main_s->map_ids.so = false;
	main_s->map_ids.we = false;
	main_s->map_ids.ea = false;
	main_s->map_ids.f = false;
	main_s->map_ids.c = false;
	main_s->no = "NO";
	main_s->so = "SO";
	main_s->we = "WE";
	main_s->ea = "EA";
	main_s->map_infos.x = 0;
	main_s->map_infos.y = 0;
	main_s->error_value = 0;
}

void	ft_check_extension(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len < 5)
		ft_error(9);
	len--;
	if (path[len] != 'b')
		ft_error(9);
	len--;
	if (path[len] != 'u')
		ft_error(9);
	len--;
	if (path[len] != 'c')
		ft_error(9);
	len--;
	if (path[len] != '.')
		ft_error(9);
	len--;
	if (path[len] == '/')
		ft_error(9);
}

int	check_main(char **av, t_map *main_s)
{
	ft_check_extension(av[1]);
	ft_init(main_s);
	ft_check_management(av[1], main_s);
	ft_rgb_convert(main_s);
	return (0);
}
