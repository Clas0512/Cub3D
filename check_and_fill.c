/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_fill.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anargul <anargul@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 16:52:34 by anargul           #+#    #+#             */
/*   Updated: 2023/07/26 14:43:38 by anargul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_check_and_fill_maptocheck(int y, int map_start, char *line)
{
	int		i;
	char	c;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
	{
		c = line[i];
		if (y == map_start && c != '1' && c != ' ')
			return (1);
		if (!(c == 'N' || c == 'S' || c == 'W'
				|| c == 'E' || c == '1' || c == '0' || c == ' '))
			return (1);
		i++;
	}
	return (0);
}

int	ft_zero_zero(char **map, t_map *main_s, int map_start)
{
	int	i;
	int	j;
	int len;

	i = map_start;
	while (i < main_s->map_infos.y + map_start)
	{
		len = ft_strlen_modded(map[i]);
		j = 0;
		printf("Str:%s\n", map[i]);
		while (map[i][j] != '\n' && map[i][j] != '\0')
		{
			if ((i == map_start || i == main_s->map_infos.y + map_start - 1 || j == 0 || j == len - 1 ) && map[i][j] == '0')
				return (1);
			else if (i > map_start && i != main_s->map_infos.y + map_start - 1 && j > 0 && j != len - 1 && map[i][j] == '0')
			{
				if (map[i - 1][j] == ' ')
					return (1);
				if (map[i + 1][j] == ' ')
					return (1);
				if (map[i][j - 1] == ' ')
					return (1);
				if (map[i][j + 1] == ' ')
					return (1);
			}
			if (map[i][j] == '0' && i != map_start && i != main_s->map_infos.y + map_start - 1)
				if (j > (int)ft_strlen_modded(map[i - 1]) - 1 || j > (int)ft_strlen_modded(map[i + 1]) - 1)
					return (1);
			j++;
		}
		i++;	
	}
	return (0);
}

int	ft_check_and_fill_maptofill(char *line, t_map *main_s)
{
	int			i;
	char		c;
	static int	z;

	main_s->original_map[z] = malloc(sizeof(char) * (main_s->map_infos.x));
	i = 0;
	while (i < main_s->map_infos.x)
	{
		c = '1';
		if (i < (int)ft_strlen_modded(line) && (line[i] == '1' || line[i] == '0'
				|| line[i] == 'N' || line[i] == 'S' || line[i] == 'E'
				|| line[i] == 'W'))
			c = line[i];
		main_s->original_map[z][i] = c;
		i++;
	}
	main_s->original_map[z][i] = '\0';
	z++;
	return (0);
}

int	ft_check_after(t_map *main_s)
{
	int		i;
	int		j;

	i = 0;
	while (main_s->original_map[i])
	{
		j = 0;
		while (main_s->original_map[i][j] != '\0')
		{
			if (i == 0 && main_s->original_map[i][j] != '1')
				return (6);
			else if (i == main_s->map_infos.y - 1 && main_s->original_map[i][j] != '1')
				return (6);
			else if (j == 0 && main_s->original_map[i][j] != '1')
				return (6);
			else if (j == main_s->map_infos.x - 1 && main_s->original_map[i][j] != '1')
				return (6);
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_check_and_fill_player_extra(bool *flag, t_map *main_s,
										int i, int j)
{
	char	c;

	c = main_s->original_map[i][j];
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (*flag == false)
		{
			main_s->p_x = j;
			main_s->p_y = i;
			main_s->player_direction = c;
			*flag = true;
		}
		else
			return (1);
	}
	return (0);
}

int	ft_check_and_fill_player(t_map *main_s)
{
	int		i;
	int		j;
	bool	flag;

	flag = false;
	i = 0;
	while (main_s->original_map[i])
	{
		j = 0;
		while (main_s->original_map[i][j])
		{
			if (ft_check_and_fill_player_extra(&flag, main_s, i, j))
				return (1);
			j++;
		}
		i++;
	}
	if (flag == false)
		return (1);
	return (0);
}
