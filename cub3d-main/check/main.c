#include "cub3d.h"

void    ft_init(t_map *main_s)
{
    main_s->map_ids.no = false;
    main_s->map_ids.so = false;
    main_s->map_ids.we = false;
    main_s->map_ids.ea = false;
    main_s->map_ids.f = false;
    main_s->map_ids.c = false;
    main_s->no = "NO";
    main_s->so = "SO";
    main_s->we = "WE";
    main_s->ea = "EA";
    main_s->map_infos.x = 0;
    main_s->map_infos.y = 0;
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
    t_map main_s;
    ft_init(&main_s);
    ft_check_management(av[1], &main_s);
    printf("\n-------map-------\n");
    for (int i = 0; i < main_s.map_infos.y; i++)
    {
        printf("%s\n", main_s.original_map[i]);
    }
    printf("-----------------\n");
    printf("\n\n\n\n--------- Main ---------\n");
    printf("x : %d\n", main_s.map_infos.x);
    printf("y : %d\n", main_s.map_infos.y);
    printf("no : %s\n", main_s.no);
    printf("so : %s\n", main_s.so);
    printf("ea : %s\n", main_s.ea);
    printf("we : %s\n", main_s.we);
    printf("-------------------\n");
    printf("The Last Way\n");
    return (0);
}