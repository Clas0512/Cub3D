/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakkus <sakkus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:00:00 by anargul           #+#    #+#             */
/*   Updated: 2023/07/28 12:14:36 by sakkus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_fill_the_id(int id, char *path, t_map *main_s)
{
	if (id == 1)
	{
		main_s->no = ft_strdup(path);
		main_s->map_ids.no = true;
	}
	else if (id == 2)
	{
		main_s->so = ft_strdup(path);
		main_s->map_ids.so = true;
	}
	else if (id == 3)
	{
		main_s->ea = ft_strdup(path);
		main_s->map_ids.ea = true;
	}
	else if (id == 4)
	{
		main_s->we = ft_strdup(path);
		main_s->map_ids.we = true;
	}
}

int	ft_check_line(char *line, t_map *main_s)
{
	char	**tmp;
	int		id;
	char	*param;		

	tmp = ft_split(line, ' ');
	id = ft_which_id(tmp[0]);
	if (ft_id_is_true(id, main_s))
		ft_error_2(2, tmp);
	param = tmp[1];
	if (!tmp[1] || tmp[2])
		ft_error_2(3, tmp);
	tmp[1] = ft_edit_nl(tmp[1]);
	free(param);
	if (id != 5 && id != 6 && ft_is_valid_path(tmp[1]) == 0)
		ft_error_2(3, tmp);
	if (id != 5 && id != 6)
		ft_fill_the_id(id, tmp[1], main_s);
	else if (ft_is_rgb(id, tmp[1], main_s) == 0)
		ft_error_2(4, tmp);
	ft_spec_tmp_free(tmp);
	return (-1);
}

int	ft_check_and_fill_map(int map_start, t_map *main_s)
{
	int	i;
	int	y;

	i = map_start;
	main_s->error_value = 0;
	ft_find_x_y(map_start, main_s);
	y = main_s->map_infos.y + i;
	main_s->original_map = malloc(sizeof(char *) * (main_s->map_infos.y + 1));
	main_s->original_map[main_s->map_infos.y] = NULL;
	if (!main_s->original_map)
		return (1);
	if (ft_zero_zero(main_s->file, main_s, map_start))
		return (8);
	while (i < y)
	{
		if (ft_check_and_fill_maptocheck(i, map_start, main_s->file[i])
			|| ft_check_and_fill_maptofill(main_s->file[i++], main_s))
			return (8);
	}
	main_s->error_value = ft_check_after(main_s);
	if (main_s->error_value != 0)
		return (main_s->error_value);
	if (ft_check_and_fill_player(main_s))
		return (5);
	return (0);
}

int	ft_is_last_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
	{
		if (line[i] == '1' || line[i] == '0')
			return (1);
		i++;
	}
	return (0);
}

int	ft_check_management(char *first_taken_map, t_map *main_s)
{
	int	i;
	int	error_value;

	main_s->file = ft_read_map(first_taken_map);
	error_value = 0;
	i = 0;
	while (main_s->file[i])
	{
		if (main_s->file[i][0] == '\n')
		{
			i++;
			continue ;
		}
		if (ft_ids_are_ok(main_s))
		{
			error_value = ft_check_and_fill_map(i, main_s);
			if (error_value != 0)
				ft_error(error_value);
			return (0);
		}
		ft_error(ft_check_line(main_s->file[i], main_s));
		i++;
	}
	return (0);
}
