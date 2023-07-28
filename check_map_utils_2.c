/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakkus <sakkus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:01:02 by anargul           #+#    #+#             */
/*   Updated: 2023/07/28 11:47:11 by sakkus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_is_valid_path(char *path)
{
	int	fd;

	fd = open(path, O_RDWR);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

void	ft_spec_tmp_free(char **tmp)
{
	int	i;

	i = 0;
	while (tmp[i])
		free(tmp[i++]);
	free(tmp);
}

int	ft_ids_are_ok(t_map *main_s)
{
	if (main_s->map_ids.no == false || main_s->map_ids.so == false
		|| main_s->map_ids.ea == false || main_s->map_ids.we == false
		|| main_s->map_ids.f == false || main_s->map_ids.c == false)
		return (0);
	return (1);
}

char	*ft_edit_nl(char *path)
{
	int		i;
	int		j;
	char	*tmp;

	tmp = path;
	i = 0;
	j = 0;
	while (path[i] != '\n')
		i++;
	path = malloc(sizeof(char) * i);
	while (j < i)
	{
		path[j] = tmp[j];
		j++;
	}
	path[i] = '\0';
	return (path);
}

int	ft_which_id(char *id)
{
	if (ft_strncmp("NO", id, 2) == 0)
		return (1);
	if (ft_strncmp("SO", id, 2) == 0)
		return (2);
	if (ft_strncmp("EA", id, 2) == 0)
		return (3);
	if (ft_strncmp("WE", id, 2) == 0)
		return (4);
	if (ft_strncmp("F", id, 1) == 0)
		return (5);
	if (ft_strncmp("C", id, 2) == 0)
		return (6);
	return (0);
}
