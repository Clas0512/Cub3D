#include "cub3d.h"

char **ft_read_map(char *file_name)
{
    char **full_file;
    int line_count;
    int fd;
    char* temp;

    fd = open(file_name, O_RDWR);
    temp = get_next_line(fd);
    line_count = 1;
    while (temp)
    {
        free(temp);
        line_count++;
        temp = get_next_line(fd);
    }
    printf("lc : %d\n", line_count);
    if (line_count < 9)
        exit(2); // map'de yeteri kadar satır yok !!!
    full_file = malloc(sizeof(char *) * (line_count + 1));
    close(fd);
    fd = open(file_name, O_RDWR);
    full_file[0] = get_next_line(fd);
    line_count = 0;
    while (full_file[line_count])
    {
        line_count++;
        full_file[line_count] = get_next_line(fd);
    }
    return (full_file);
}

void    ft_check_ids(t_map *suliman)
{
    char **file;
    int i;

    file = suliman->file;
    i = 0;
    while (file[i])
    {
        ft_identifier_fill_check(file[i], suliman);
        i++;
    }
    if (suliman->map_ids.no == 1)
        printf("no: true\n");
    if (suliman->map_ids.so == 1)
        printf("so: true\n");
    if (suliman->map_ids.ea == 1)
        printf("ea: true\n");
    if (suliman->map_ids.we == 1)
        printf("we: true\n");
    
    if (ft_is_ok_ids(suliman) == 0)
        exit(3); // idler yok.
}

void    ft_check_map_management(char *first_taken_map, t_map *suliman)
{
    suliman->file = ft_read_map(first_taken_map); // map'i tamamen okunup structımızın "file" adındaki string dizisine atılır.
    for (size_t i = 0; suliman->file[i]; i++)
    {
        printf("ft_cmm: %s", suliman->file[i]);
    }
    printf("\n");
    ft_check_ids(suliman);
}