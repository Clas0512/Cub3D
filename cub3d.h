/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakkus <sakkus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:56:13 by anargul           #+#    #+#             */
/*   Updated: 2023/07/28 13:01:30 by sakkus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

typedef struct s_mini_map
{
	double	units;
	int		x;
	int		y;
}				t_mini_map;

typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		pitch;
}	t_ray;

typedef struct s_texture
{
	double	wall_x;
	double	step;
	double	tex_pos;
	int		color;
	int		text_x;
	int		text_y;
}	t_texture;

typedef struct s_put
{
	int	color;
	int	start;
	int	end;
	int	x;
}				t_put;

enum	e_dir
{
	NORTH,
	SOUTH,
	EAST,
	WEST,
};

enum	e_keys
{
	W,
	S,
	A,
	D,
	RIGHT,
	LEFT,
};

typedef struct s_map_informations
{
	int	x;
	int	y;
}	t_map_informations;

typedef struct s_map_ids
{
	bool	no;
	bool	so;
	bool	we;
	bool	ea;
	bool	f;
	bool	c;
}	t_map_ids;

typedef struct s_map
{
	t_map_informations	map_infos;
	t_map_ids			map_ids;
	char				**original_map;
	char				**file;
	char				*no;
	char				*so;
	char				*we;
	char				*ea;
	int					p_x;
	int					p_y;
	int					f[3];
	int					c[3];
	int					frgb;
	int					crgb;
	int					player_direction;
	int					error_value;
	int					r;
	int					g;
	int					b;
}	t_map;

typedef struct s_image
{
	void	*img_adress;
	void	*buffer;
	int		bbp;
	int		size_line;
	int		endian;
	int		width;
	int		height;
}				t_image;

typedef struct s_player
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		speed;
	double		direction;
}				t_player;

typedef struct s_win
{
	void	*win_addres;
	int		width_screen;
	int		height_screen;
	int		floor_color;
	int		ceiling_color;
}		t_win;

typedef struct s_data
{
	t_win		*win;
	t_player	*player;
	t_image		*screen_image;
	t_image		*walls;
	void		*mlx;
	char		**map;
	int			keycode[7];
	int			x_len;
	int			y_len;
}				t_data;

int		ft_zero_zero(char **map, t_map *main_s, int map_start);
void	ft_error_2(int error, char **tmp);
int		ft_id_is_true(int id, t_map *main_s);
int		ft_id_is_true_extra(int id, t_map *main_s);
int		ft_which_id(char *id);
char	*ft_edit_nl(char *path);
int		ft_ids_are_ok(t_map *main_s);
int		ft_is_valid_path(char *path);
void	ft_spec_tmp_free(char **tmp);
void	ft_fill_the_rgb_f(int r, int g, int b, t_map *main_s);
void	ft_fill_the_rgb_c(int r, int g, int b, t_map *main_s);
int		ft_check_and_fill_maptocheck(int y, int map_start, char *line);
int		ft_check_after(t_map *main_s);
int		ft_check_and_fill_player(t_map *main_s);
int		ft_check_and_fill_player_extra(bool *flag, t_map *main_s, int i, int j);
int		ft_check_and_fill_maptofill(char *line, t_map *main_s);
void	ft_find_x_y(int j, t_map *main_s);
int		ft_check_and_fill_map(int map_start, t_map *main_s);
char	**ft_read_map(char *file_name);
int		ft_check_management(char *first_taken_map, t_map *main_s);
int		ft_is_ok_ids(t_map *main_s);
int		check_main(char **av, t_map *main_s);
void	init_data(t_map *map, t_data *data);
int		image_color(int x, int y, t_image *img);
size_t	ft_strlen_modded(const char *s);
void	put_cle_floo(t_data *data);
double	is_zero(double x);
void	init_map(t_data *data);
void	start_end_calc(t_ray *ray, int height);
void	dda(t_ray *ray, char **map);
void	step_calc(t_player *player, t_ray *ray);
void	init_ray(int x, t_data *data, t_ray *ray);
void	ft_rgb_convert(t_map *map);
void	calc_rot(t_data *data, double rot_speed);
void	ft_error(int error);
void	free_wall_name(t_map *map);
int		ft_is_rgb(int id, char *rgb, t_map *main_s);
void	put_image(t_put *put, t_image *img);
void	get_dir(t_player *player);
int		key_press(int keycode, t_data *data);
int		ft_exit(int keycode, t_data *data);
int		key_release(int keycode, t_data *data);
int		keyboard(t_data *data);
int		calc_move(t_data *data, int sign, double move_speed);
int		calc_move_d(t_data *data, int sign, double move_speed);
void	calc_rot(t_data *data, double rot_speed);

#endif