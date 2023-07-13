#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <math.h>
# include <stdbool.h>
# include <fcntl.h>
# include "gnl/get_next_line.h"
# include "libft/libft.h"


# define NO "NO"
# define SO "SO"
# define EA "EA"
# define WE "WE"

typedef struct s_player{
    int p_x;
    int p_y;
    int p_direction; // N=1 S=2 E=3 W=4
}       t_player;

typedef struct s_map_informations{
    int x;
    int y;
}       t_map_informations;

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
    t_map_informations map_infos;
    t_player player;
    char    **original_map;
    char    **file;
    char    *no;
    char    *so;
    char    *we;
    char    *ea;
    int     f[3];
    int     c[3];
}       t_map;

int     ft_check_management(char *first_taken_map, t_map *main_s);
int     ft_is_ok_ids(t_map *main_s);

#endif