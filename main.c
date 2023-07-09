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
    suliman->map_infos.x = 0;
    suliman->map_infos.y = 0;
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
    ft_check_management(av[1], &suliman);
    printf("\n-------map-------\n");
    for (int i = 0; i < suliman.map_infos.y; i++)
    {
        printf("%s\n", suliman.original_map[i]);
    }
    printf("-----------------\n");
    printf("\n\n\n\n--------- Main ---------\n");
    printf("x : %d\n", suliman.map_infos.x);
    printf("y : %d\n", suliman.map_infos.y);
    printf("no : %s\n", suliman.no);
    printf("so : %s\n", suliman.so);
    printf("ea : %s\n", suliman.ea);
    printf("we : %s\n", suliman.we);
    printf("-------------------\n");
    printf("The Last Way\n");
    return (0);
}