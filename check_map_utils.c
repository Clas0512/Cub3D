/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anargul <anargul@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:10:03 by anargul           #+#    #+#             */
/*   Updated: 2023/07/25 17:53:42 by anargul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

size_t	ft_strlen_modded(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	return (i);
}

void	ft_find_x_y(int j, t_map *main_s)
{
	int	len;
	int	i;

	main_s->map_infos.x = 0;
	main_s->map_infos.y = 0;
	i = 0;
	while (main_s->file[j] && *main_s->file[j] != '\n'
		&& *main_s->file[j] != '\0')
	{
		len = ft_strlen_modded(main_s->file[j]);
		if (len > main_s->map_infos.x)
			main_s->map_infos.x = len;
		j++;
		i++;
	}
	main_s->map_infos.y = i;
}

void	free_double(char **file)
{
	int	x;

	x = 0;
	while (file[x])
		free(file[x++]);
	free(file);
}

void	ft_error(int error)
{
	if (error == -1)
		return ;
	else if (error == 0)
	{
		perror("Missing Map Line Error!");
		exit (-1);
	}
	else if (error == 1)
		perror("Allocation Error!");
	else if (error == 5)
		perror("Player Error!");
	else if (error == 6)
		perror("Wall Error!");
	else if (error == 7)
		perror("Player Error!");
	exit(1);
}

int	ft_is_rgb(int id, char *rgb, t_map *main_s)
{
	char	**rgb_2d;
	int		r;
	int		g;
	int		b;
	int		i;

	rgb_2d = ft_split(rgb, ',');
	if (!rgb)
		return (0);
	if (!rgb_2d[2])
		return (0);
	r = ft_atoi(rgb_2d[0]);
	g = ft_atoi(rgb_2d[1]);
	b = ft_atoi(rgb_2d[2]);
	i = 0;
	while (rgb_2d[i])
		free(rgb_2d[i++]);
	free(rgb_2d);
	if (r > 255 || r < 0 || g > 255 || g < 0 || b > 255 || b < 0)
		return (0);
	if (id == 5)
		ft_fill_the_rgb_f(r, g, b, main_s);
	if (id == 6)
		ft_fill_the_rgb_c(r, g, b, main_s);
	return (1);
}
