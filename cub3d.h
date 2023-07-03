#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <math.h>
# include <stdbool.h>
# include <fcntl.h>
# include "gnl/get_next_line.h"
# include "libft/libft.h"

// enum {
//     NO,
//     SO,
//     EA,
//     WE
// };

# define NO "NO"
# define SO "SO"
# define EA "EA"
# define WE "WE"

typedef struct s_map_ids{
    bool no;
    bool so;
    bool we;
    bool ea;
    bool f;
    bool c;
}       t_map_ids;

typedef struct s_map{
    t_map_ids map_ids;
    char    **file;
    char    *no;
    char    *so;
    char    *we;
    char    *ea;
    int     f[3];
    int     c[3];
}       t_map;

void    ft_check_map_management(char *first_taken_map, t_map *suliman);
void    ft_identifier_fill(char *id, char *path, t_map *suliman);
void    ft_identifier_fill_check(char *line, t_map *suliman);
int ft_is_ok_ids(t_map *suliman);

#endif