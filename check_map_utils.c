/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakkus <sakkus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:10:03 by anargul           #+#    #+#             */
/*   Updated: 2023/07/28 15:45:37 by sakkus           ###   ########.fr       */
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

void	ft_error(int error)
{
	if (error == -1)
		return ;
	else if (error == 0)
		printf("Missing Map Line Error!\n");
	else if (error == 1)
		printf("Allocation Error!\n");
	else if (error == 5 || error == 7)
		printf("Player Error!\n");
	else if (error == 6)
		printf("Wall Error!\n");
	else if (error == 8)
		printf("Unknown Character!\n");
	else if (error == 9)
		printf("Invalid Path Extension!\n");
	exit(1);
}

int	ft_rgb_fill(int *r, int *g, int *b, char **rgb_2d)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < 3)
	{
		while (rgb_2d[i][j] != '\0')
		{
			if (ft_isdigit(rgb_2d[i][j]) == 0)
				return (0);
			j++;
		}
		i++;
	}
	*r = ft_atoi(rgb_2d[0]);
	*g = ft_atoi(rgb_2d[1]);
	*b = ft_atoi(rgb_2d[2]);
	return (0);
}

int	ft_is_rgb(int id, char *rgb, t_map *main_s)
{
	char	**rgb_2d;
	int		i;

	rgb_2d = ft_split(rgb, ',');
	if (!rgb)
		return (0);
	if (!rgb_2d[2])
		return (0);
	if (ft_rgb_fill(&main_s->r, &main_s->g, &main_s->b, rgb_2d))
		return (0);
	i = 0;
	while (rgb_2d[i])
		free(rgb_2d[i++]);
	free(rgb_2d);
	if (main_s->r > 255 || main_s->r < 0 || main_s->g > 255 || main_s->g < 0
		|| main_s->b > 255 || main_s->b < 0)
		return (0);
	if (id == 5)
		ft_fill_the_rgb_f(main_s->r, main_s->g, main_s->b, main_s);
	if (id == 6)
		ft_fill_the_rgb_c(main_s->r, main_s->g, main_s->b, main_s);
	return (1);
}
