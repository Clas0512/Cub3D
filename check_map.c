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
        exit(2); // map'de yeteri kadar satır yok !!
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

int ft_id_is_true_extra(int id, t_map *main_s)
{
    if (id == 5)
    {
        if (main_s->map_ids.f == true)
            return (1);
    }
    if (id == 6)
    {
        if (main_s->map_ids.c == true)
            return (1);
    }
    return (0);
}

int ft_id_is_true(int id, t_map *main_s)
{
    if (id == 1)
    {
        if (main_s->map_ids.no == true)
            return (1);
    }
    else if (id == 2)
    {
        if (main_s->map_ids.so == true)
            return (1);
    }
    else if (id == 3)
    {
        if (main_s->map_ids.ea == true)
            return (1);
    }
    else if (id == 4)
    {
        if (main_s->map_ids.we == true)
            return (1);
    }
    return (ft_id_is_true_extra(id, main_s));
}

void    ft_fill_the_rgb(int id, int r, int g, int b, t_map *main_s)
{
    if (id == 5)
    {
        main_s->f[0] = r;
        main_s->f[1] = g;
        main_s->f[2] = b;
        main_s->map_ids.f = true;
    }
    if (id == 6)
    {
        main_s->c[0] = r;
        main_s->c[1] = g;
        main_s->c[2] = b;
        main_s->map_ids.c = true;
    }
}

void    ft_fill_the_id(int id, char *path, t_map *main_s)
{
    if (id == 1)
    {
        main_s->no = path;
        main_s->map_ids.no = true;
    }
    else if (id == 2)
    {
        main_s->so = path;
        main_s->map_ids.so = true;
    }
    else if (id == 3)
    {
        main_s->ea = path;
        main_s->map_ids.ea = true;
    }
    else if (id == 4)
    {
        main_s->we = path;
        main_s->map_ids.we = true;
    }
}

int ft_is_rgb(int id, char *rgb, t_map *main_s)
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
    ft_fill_the_rgb(id, r, g, b, main_s);
    return (1);
}

int ft_is_valid_path(char *path)
{
    int fd;

    fd = open(path, O_RDONLY);
    printf(" ww %s\n", path);
    if (fd == -1)
        exit (222);
    close(fd);
    return (0);
}

int ft_check_line(char *line, t_map *main_s)
{
    char    **tmp;
    int     id;

    tmp = ft_split(line, ' ');
    id = ft_which_id(tmp[0]);
    if (ft_id_is_true(id, main_s))
        return (1);
    // if (ft_is_valid_path(tmp[1]) == 0)
    //     return (1);
    if (id != 5 && id != 6)
        ft_fill_the_id(id, tmp[1], main_s);
    else if (ft_is_rgb(id, tmp[1], main_s) == 0)
        return (1);
    return (0);
}

int ft_ids_are_ok(t_map *main_s)
{
    if (main_s->map_ids.no == false || main_s->map_ids.so == false ||
        main_s->map_ids.ea == false || main_s->map_ids.we == false ||
        main_s->map_ids.f == false || main_s->map_ids.c == false)
        return (0);
    return (1);
}

// harita koşulları : 
//             1-) haritada bulunabilecek olası karakterler : N, S, W, E, 1, 0
//             2-) dikdörtgen olması koşulu
//             3-) 4 bir tarafıııım 1'ler ile çevriliiiğ
//             4-) boşluk karakterleri dışında harita bölnüemez
//             5-) bu 5 kural hiç bir şekilde değiştirilemez değiştirilmesi teklif dahi edilemez!

size_t	ft_strlen_modded(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	return (i);
}

void    ft_find_x_y(int j, t_map *main_s)
{
    int len;
    int i;

    main_s->map_infos.x = 0;
    main_s->map_infos.y = 0;
    i = 0;
    while (main_s->file[j] && *main_s->file[j] != '\n' && *main_s->file[j] != '\0')
    {
        // printf("satir %d. = '%s'", j, main_s->file[j]);
        len = ft_strlen_modded(main_s->file[j]);
        if (len > main_s->map_infos.x)
            main_s->map_infos.x = len;
        j++;
        i++;
    }
    main_s->map_infos.y = i;
    // printf("x : %d\n", main_s->map_infos.x);
    // printf("y : %d\n", main_s->map_infos.y);
}

int ft_check_and_fill_maptocheck(int y, int map_start, char *line)
{
    int     i;
    char    c;

    i = 0;
    while (line[i] != '\n' && line[i] != '\0')
    {
        c = line[i];
        if (y == map_start && c != '1' && c != ' ')
            exit (199);
        if (!(c == 'N' || c == 'S' || c == 'W' ||
                c == 'E' || c == '1' || c == '0' || c == ' '))
            exit (99);
        i++;
    }
    return (0);
}

int ft_check_and_fill_maptofill(char *line, t_map *main_s)
{
    int         i;
    char        c;
    static int  z;

    main_s->original_map[z] = malloc(sizeof(char) * (main_s->map_infos.x + 1));
    i = 0;
    while (i < main_s->map_infos.x)
    {
        c = '1';
        if (i < (int)ft_strlen_modded(line) && (line[i] == '1' || line[i] == '0' || line[i] == 'N' || line[i] == 'S' ||
                    line[i] == 'E' || line[i] == 'W'))
            c = line[i];
        // printf("%d. %c\n", i, c);
        main_s->original_map[z][i] = c;
        i++;
    }
    main_s->original_map[z][i] = '\0';
    // printf("%d. satir : '%s'\n", z, main_s->original_map[z]);
    z++;
    return (1);
}

int ft_check_after(t_map *main_s)
{
    int     i;
    int     j;
    char    c;

    i = 0;
    while (main_s->original_map[i])
    {
        j = 0;
        while (main_s->original_map[i][j])
        {
            c = main_s->original_map[i][j];
            if (i == 0 && c != '1')
                exit (145);
            else if (i == main_s->map_infos.y - 1 && c != '1')
            {
                printf("%d,%d - %c\n", j, i, c);
                exit (146);
            }
            else if (j == 0 && c != '1')
                exit (147);
            else if (j == main_s->map_infos.x - 1 && c != '1')
                exit (148);
            j++;
        }
        i++;
    }
    return (0);
}

int ft_check_and_fill_player_extra(char c, bool *flag, t_map *main_s, int i, int j)
{
    if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
    {
        if (*flag == false)
        {
            main_s->player.p_x = j;
            main_s->player.p_y = i;
            *flag = true;
        }
        else
            exit(51);
    }
    return (0);
}

int ft_check_and_fill_player(t_map *main_s)
{
    int     i;
    int     j;
    bool    flag;

    flag = false;
    i = 0;
    while (main_s->original_map[i])
    {
        j = 0;
        while (main_s->original_map[i][j])
        {
            ft_check_and_fill_player_extra(main_s->original_map[i][j], &flag, main_s, i, j);
            j++;
        }
        i++;
    }
    if (flag == false)
        return (1);
    return (0);
}

int ft_check_and_fill_map(int map_start, t_map *main_s)
{
    int i;
    int y;

    i = map_start;
    ft_find_x_y(map_start, main_s);
    y = main_s->map_infos.y + i;
    main_s->original_map = malloc(sizeof(char *) * (main_s->map_infos.y + 1));
    if (!main_s->original_map)
        exit (13);
    while (i < y) // i değişkeni map'in dosyadaki BAŞLANGIÇ satırından başlamış olan değişken
    {
        ft_check_and_fill_maptocheck(i, map_start, main_s->file[i]);
        ft_check_and_fill_maptofill(main_s->file[i], main_s);
        i++;
    }
    if (ft_check_after(main_s))
        exit (149);
    if (ft_check_and_fill_player(main_s))
    {
        perror("Player is not exist!");
        exit (52);
    }
    return (0);
}

int ft_check_management(char *first_taken_map, t_map *main_s)
{
    int i;

    main_s->file = ft_read_map(first_taken_map); // map'i tamamen okunup structımızın "file" adındaki string dizisine atılır.
    i = 0;
    while (main_s->file[i])
    {
        if (main_s->file[i][0] == '\n')
        {
            i++;
            continue ;
        }
        if (ft_ids_are_ok(main_s))
        {
            if (ft_check_and_fill_map(i, main_s))
                exit (31);
            return (0);
        }
        if (ft_check_line(main_s->file[i], main_s))
            exit (62);
        i++;
    }
    return (0);
}