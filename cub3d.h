#ifndef CUB3D_H
# define CUB3D_H


# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <stdbool.h>
# include <fcntl.h>
# include "mlx/mlx.h"
# include "gnl/get_next_line.h"
# include "libft/libft.h"

# define PI		3.14159265
# define PURPLE 0xa354ff
# define RADIAN 0.0174533
# define GREEN	0x25bc17
# define WHITE	0xffffff
# define RED	0XF51313
# define LILAC	0x8C1DEE
# define BLACK	0x000000
# define GRAY	0x726E6E
# define NO "NO"
# define SO "SO"
# define EA "EA"
# define WE "WE"

enum	e_dir
{
	NORTH,
	SOUTH,
	EAST,
	WEST,
};

typedef struct s_map_informations
{
    int x;
    int y;
}       t_map_informations;

typedef struct s_player
{
	int		p_x;
	int		p_y;
    int		p_direction; // N=1 S=2 E=3 W=4
	float	p_delta_x;
	float	p_delta_y;
	float	alpha;
	int 	index;
}       t_player;

typedef struct s_map_ids
{
    bool no;
    bool so;
    bool we;
    bool ea;
    bool f;
    bool c;
}       t_map_ids;

typedef struct s_map
{
	t_map_informations	map_infos;
	t_player			player;
	t_map_ids			map_ids;
    char    			**original_map;
    char    			**file;
    char    			*no;
    char    			*so;
    char    			*we;
    char    			*ea;
    int     			f[3];
    int     			c[3];
	int     frgb;
    int     crgb;
}       t_map;

typedef struct s_image
{
	void	*image;
	char	*buffer;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}       t_image;

typedef struct	s_data
{
	t_map		*map;
	t_player	*player;
	t_image		*wall_imgs; // duvar imagelerini tutacak
	t_image		*win_img_2d;
	t_image		*win_img_3d;
	int			*raycast;
	void 		*mlx;
	void 		*win;
	int			width;
	int			height;
	int			units;
}				t_data;


void	init_data(t_data *data);
void	init_map(t_data *data);
void	init_raycast(t_data *data);
void	init_image(t_data *data);
void	init_3d_map(t_data *data);
int     ft_check_management(char *first_taken_map, t_map *main_s);
int     ft_is_ok_ids(t_map *main_s);
int     check_main(char **av, t_map *main_s);
int 	keyboard(int keycode, t_data *data);
int 	shutdown(void *s_data);

#endif