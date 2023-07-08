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

int ft_which_id(char *id)
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

int ft_id_is_true_extra(int id, t_map *suliman)
{
    if (id == 5)
    {
        if (suliman->map_ids.f == true)
            return (1);
    }
    if (id == 6)
    {
        if (suliman->map_ids.c == true)
            return (1);
    }
    return (0);
}

int ft_id_is_true(int id, t_map *suliman)
{
    if (id == 1)
    {
        if (suliman->map_ids.no == true)
            return (1);
    }
    else if (id == 2)
    {
        if (suliman->map_ids.so == true)
            return (1);
    }
    else if (id == 3)
    {
        if (suliman->map_ids.ea == true)
            return (1);
    }
    else if (id == 4)
    {
        if (suliman->map_ids.we == true)
            return (1);
    }
    return (ft_id_is_true_extra(id, suliman));
}

void    ft_fill_the_rgb(int id, int r, int g, int b, t_map *suliman)
{
    if (id == 5)
    {
        suliman->f[0] = r;
        suliman->f[1] = g;
        suliman->f[2] = b;
        suliman->map_ids.f = true;
    }
    if (id == 6)
    {
        suliman->c[0] = r;
        suliman->c[1] = g;
        suliman->c[2] = b;
        suliman->map_ids.c = true;
    }
}

void    ft_fill_the_id(int id, char *path, t_map *suliman)
{
    if (id == 1)
    {
        suliman->no = path;
        suliman->map_ids.no = true;
    }
    else if (id == 2)
    {
        suliman->so = path;
        suliman->map_ids.so = true;
    }
    else if (id == 3)
    {
        suliman->ea = path;
        suliman->map_ids.ea = true;
    }
    else if (id == 4)
    {
        suliman->we = path;
        suliman->map_ids.we = true;
    }
}

int ft_is_rgb(int id, char *rgb, t_map *suliman)
{
    char **rgb_2d;
    int r;
    int g;
    int b;

    rgb_2d = ft_split(rgb, ',');
    if (!rgb)
        return (0);
    if (!rgb_2d[2])
        return (0);
    r = ft_atoi(rgb_2d[0]);
    g = ft_atoi(rgb_2d[1]);
    b = ft_atoi(rgb_2d[2]);
    if (r > 255 || r < 0 || g > 255 || g < 0 || b > 255 || b < 0)
        return (0);
    ft_fill_the_rgb(id, r, g, b, suliman);
    return (1);
}

int ft_check_line(char *line, t_map *suliman)
{
    char    **tmp;
    int     i;
    int     id;

    i = 0;
    tmp = ft_split(line, ' ');
    id = ft_which_id(tmp[0]);
    if (ft_id_is_true(id, suliman))
        return (1);
    // if (ft_is_valid_path(tmp[2], suliman) == 0)
    //     return (1);
    if (id != 5 && id != 6)
        ft_fill_the_id(id, tmp[1], suliman);
    else if (ft_is_rgb(id, tmp[1], suliman) == 0)
        return (1);
    return (0);
}

int ft_ids_are_ok(t_map *suliman)
{
    if (suliman->map_ids.no == false || suliman->map_ids.so == false ||
        suliman->map_ids.ea == false || suliman->map_ids.we == false ||
        suliman->map_ids.f == false || suliman->map_ids.c == false)
        return (0);
    return (1);
}

// harita koşulları : 
//             1-) haritada bulunabilecek olası karakterler : N, S, W, E, 1, 0
//             2-) dikdörtgen olması koşulu
//             3-) 4 bir tarafıııım 1'ler ile çevriliiiğ
//             4-) boşluk karakterleri dışında harita bölnüemez
//             5-) bu 5 kural hiç bir şekilde değiştirilemez değiştirilmesi teklif dahi edilemez!

void    ft_find_x_y(int j, t_map *suliman)
{
    int len;
    int i;

    suliman->map_infos.x = 0;
    suliman->map_infos.y = 0;
    i = 0;
    while (*suliman->file[j] != '\n' && *suliman->file[j] != '\0')
    {
        len = ft_strlen(*suliman->file[j]);
        if (len > suliman->map_infos.x)
            suliman->map_infos.x = len;
        j++;
        i++;
    }
    suliman->map_infos.y = i;
}

// void ft_fill_map_line

int ft_check_and_fill_maptomap(int y, char *line)
{
    int     i;
    char    c;

    i = 0;
    while (line[i] != '\n' && line[i] != '\0')
    {
        c = line[i];
        if (y == 0 && !(c == '1' || c == ' '))
            exit (199);
        if (!(c == 'N' || c == 'S' || c == 'W' ||
                c == 'E' || c == '1' || c == '0' || c == ' '))
            exit (99);
        i++;
    }
    
    return (0);
}

int ft_check_and_fill_map(int j, t_map *suliman)
{
    int i;
    int y;

    i = 0;
    y = suliman->map_infos.y;
    ft_find_x_y(j, suliman);
    while (i < y)
    {
        ft_check_and_fill_maptomap(i, suliman->file[y]);
        i++;
    }
    return (0);
}

int ft_check_management(char *first_taken_map, t_map *suliman)
{
    int i;

    suliman->file = ft_read_map(first_taken_map); // map'i tamamen okunup structımızın "file" adındaki string dizisine atılır.
    i = 0;
    while (suliman->file[i])
    {
        if (suliman->file[i][0] == '\n')
        {
            i++;
            continue ;
        }
        if (ft_ids_are_ok(suliman))
        {
            if (ft_check_and_fill_map(i, suliman))
                exit(31);
            return (0);
        }
        if (ft_check_line(suliman->file[i], suliman))
            exit (62);
        i++;
    }
    return (0);
}