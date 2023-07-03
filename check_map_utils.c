#include "cub3d.h"

int ft_is_ok_ids(t_map *suliman)
{
    if (suliman->map_ids.no == true && suliman->map_ids.so == true &&
        suliman->map_ids.ea == true && suliman->map_ids.we == true &&
        suliman->map_ids.c == true && suliman->map_ids.f == true)
        return (1);
    return (0);
}

int get_false_id(t_map *suliman)
{
    if (suliman->map_ids.no == false)
        return (0);
    else if (suliman->map_ids.so == false)
        return (1);
    else if (suliman->map_ids.ea == false)
        return (2);
    else if (suliman->map_ids.we == false)
        return (3);
    return (4);
}

void    ft_identifier_fill(char *id, char *path, t_map *suliman)
{
    if(ft_strncmp(id, NO, 2) == 0)
    {
        suliman->no = path;
        suliman->map_ids.no = true;
    }
    else if (ft_strncmp(id, SO, 2) == 0)
    {
        suliman->so = path;
        suliman->map_ids.so = true;
    }
    else if (ft_strncmp(id, EA, 2) == 0)
    {
        suliman->ea = path;
        suliman->map_ids.ea = true;
    }
    else if (ft_strncmp(id, WE, 2) == 0)
    {
        suliman->we = path;
        suliman->map_ids.we = true;
    }
}

void    ft_identifier_fill_check(char *line, t_map *suliman)
{
    char    **splitted;
    int     i;
    int     id;
    char    id_array[4][2] = {NO, SO, EA, WE};

    id = get_false_id(suliman);
    if (id < 0 || id > 3)
        exit(0);
    splitted = ft_split(line, ' ');
    i = 0;
    while (splitted[i])
    {
        if (splitted[i + 1] && ft_strncmp(splitted[i], id_array[id], 2) == 0)
        {
            ft_identifier_fill(splitted[i], splitted[i + 1], suliman);
            return ;
        }
        i++;
    }
    free(splitted);
    return ;
}