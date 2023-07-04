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
    // int fd;
    int i;
    i = 0;
    char **map;
    map = malloc(sizeof(char *) * 20);
    (void)ac;
    (void)av;
    t_map suliman;
    ft_init(&suliman);
    ft_check_map_management(av[1], &suliman);
    printf("MAIN: %s\n",suliman.no);
    // fd = open(av[1], O_RDWR);
    // map[i] = get_next_line(fd);
    // while (map[i])
    // {
    //     i++;
    //     map[i] = get_next_line(fd);
    // }
    // for (size_t i = 0; map[i]; i++)
    //     printf("%s", map[i]);
    return (0);
}