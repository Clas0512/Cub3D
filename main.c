#include "cub3d.h"

void    ft_init(t_map *suliman)
{
    suliman->map_ids.no = false;
    suliman->map_ids.so = false;
    suliman->map_ids.we = false;
    suliman->map_ids.ea = false;
    suliman->map_ids.f = false;
    suliman->map_ids.c = false;
    suliman->no = "NO";
    suliman->so = "SO";
    suliman->we = "WE";
    suliman->ea = "EA";
}

int main(int ac, char **av)
{
    (void)ac;
    t_map suliman;
    ft_init(&suliman);
    ft_check_map_management(av[1], &suliman);

    return (0);
}