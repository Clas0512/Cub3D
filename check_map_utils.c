#include "cub3d.h"

int ft_is_ok_ids(t_map *suliman)
{
    if (suliman->map_ids.no == true && suliman->map_ids.so == true &&
        suliman->map_ids.ea == true && suliman->map_ids.we == true)
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
    // printf("ZORT\n");
    if (ft_strncmp(id, NO, 2) == 0)
    {
        if (suliman->map_ids.no == true)
            exit(31);
        suliman->no = ft_strdup(path);
        suliman->map_ids.no = true;
    }
    if (ft_strncmp(id, SO, 2) == 0)
    {
        if (suliman->map_ids.so == true)
            exit(31);
        suliman->so = ft_strdup(path);
        suliman->map_ids.so = true;
    }
    if (ft_strncmp(id, EA, 2) == 0)
    {
        if (suliman->map_ids.ea == true)
            exit(31);
        suliman->ea = ft_strdup(path);
        suliman->map_ids.ea = true;
    }
    if (ft_strncmp(id, WE, 2) == 0)
    {
        if (suliman->map_ids.we == true)
            exit(31);
        suliman->we = ft_strdup(path);
        suliman->map_ids.we = true;
    }
}

void    ft_zort(t_map *suliman, char **splitted)
{
    int i;

    i = 0;

    while (splitted[i])
    {
        // printf("->\n");
        if (splitted[i + 1] && ft_strncmp(splitted[i], NO, 2) == 0 && suliman->map_ids.no == false)
            ft_identifier_fill(splitted[i], splitted[i + 1], suliman);
        if (splitted[i + 1] && ft_strncmp(splitted[i], SO, 2) == 0 && suliman->map_ids.so == false)
            ft_identifier_fill(splitted[i], splitted[i + 1], suliman);
        if (splitted[i + 1] && ft_strncmp(splitted[i], EA, 2) == 0 && suliman->map_ids.ea == false)
            ft_identifier_fill(splitted[i], splitted[i + 1], suliman);
        if (splitted[i + 1] && ft_strncmp(splitted[i], WE, 2) == 0 && suliman->map_ids.we == false)
            ft_identifier_fill(splitted[i], splitted[i + 1], suliman);
        i++;
    }
}

void    ft_identifier_fill_check(char *line, t_map *suliman)
{
    char    **splitted;
    int     i;
    int     id;
    // char    id_array[4][2] = {NO, SO, EA, WE};

    id = get_false_id(suliman);
    if (id < 0 || id > 3)
        exit(10);
    splitted = ft_split(line, ' ');
    i = 0;
    for (size_t i = 0; splitted[i]; i++)
    {
        printf("splitted line asd: %s\n",splitted[i]);
    }
    // sorun burda la gardaş

    ft_zort(suliman, splitted);
    
    // 
    free(splitted);
    return ;
}