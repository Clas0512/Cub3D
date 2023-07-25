/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_fill.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anargul <anargul@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 16:52:34 by anargul           #+#    #+#             */
/*   Updated: 2023/07/25 17:54:46 by anargul          ###   ########.fr       */
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
			exit (1);
		if (!(c == 'N' || c == 'S' || c == 'W'
				|| c == 'E' || c == '1' || c == '0' || c == ' '))
			exit (2);
		i++;
	}
	return (0);
}

int	ft_check_and_fill_maptofill(char *line, t_map *main_s)
{
	int			i;
	char		c;
	static int	z;

	main_s->original_map[z] = malloc(sizeof(char) * (main_s->map_infos.x + 1));
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
	return (1);
}

int	ft_check_after(t_map *main_s)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	while (main_s->original_map[i])
	{
		j = 0;
		while (main_s->original_map[i][j])
		{
			c = main_s->original_map[i][j];
			if (i == 0 && c != '1')
				return (6);
			else if (i == main_s->map_infos.y - 1 && c != '1')
				return (6);
			else if (j == 0 && c != '1')
				return (6);
			else if (j == main_s->map_infos.x - 1 && c != '1')
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
