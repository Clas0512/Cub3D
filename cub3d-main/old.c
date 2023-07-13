#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "mlx/mlx.h"

# define PI		3.14159265
# define GREEN	0x25bc17
# define WHITE	0xffffff
# define RED	0XF51313
# define LILAC	0x8C1DEE
# define BLACK	0x000000

struct s_data{
	int		width;
	int		height;
	int		size;
	int		units;
	void 	*mlx;
	void 	*win;
	
} data;

struct s_image{
	void	*image;
	char	*buffer;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int (*calc_x)(int);
	int (*calc_y)(int);
} image;

struct s_player
{
	float	x;
	float	y;
	float	delta_x;
	float	delta_y;
	float	alpha;
	float	m;
	float	diagonal;
	int 	index;
	int 	size;
} player;


int map[] = {
	1, 1, 1, 1, 1, 1,
	1, 0, 1, 0, 0, 1,
	1, 0, 1, 0, 0, 1,
	1, 0, 1, 0, 0, 1,
	1, 0, 0, -1, 0, 1,
	1, 0, 0, 0, 0, 1,
	1, 0, 0, 1, 0, 1,
	1, 1, 1, 1, 1, 1,	
};

void move(int x, int y);
void map_init(int x, int y);

int	calc_x(int index){
	return ((index % 6) * data.units);
}

int	calc_y(int index){
	return ((index / 6) * data.units);
}

void	init_data(){
	data.units = 128;
	player.size = data.units / 8;
	data.width = 6;
	data.height = (sizeof(map) / sizeof(int)) / data.width;
	data.size = sizeof(map) / sizeof(int);
	player.delta_x = cos(player.alpha)*5;
	player.delta_y = sin(player.alpha)*5;
	printf("delta_x:%f, delta_y:%f", player.delta_x, player.delta_y);
	// printf("data size: %d\n", data.size);
	data.width *= data.units, data.height *= data.units;
	printf("width: %d height: %d\n", data.width, data.height);
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, data.width, data.height, "hi");
	image.image = mlx_new_image(data.mlx, data.width, data.height);
	image.buffer = mlx_get_data_addr(image.image, &(image.bits_per_pixel), &(image.size_line), &(image.endian));
	image.calc_y = &calc_y;
	image.calc_x = &calc_x;
	// image.size_line /= 4;
	// printf("bits: %d\nsize_line: %d\n,endian: %d\n", image.bits_per_pixel, image.size_line, image.endian);
}

int shutdown(void *s_data)
{
	(void)s_data;
	printf("Pencerenin çarpı(x) tuşuna basıldı.\n");
	exit(0);
}

int keyboard(int keycode, void *n)
{
	(void)n;
	int x = player.x, y = player.y;
	if (keycode == 119 || keycode == 13){
		printf("W tuşuna basıldı.\n");
		y += player.delta_y;
		x += player.delta_x;
	}
	else if (keycode == 115 || keycode == 1){
		printf("S tuşuna basıldı.\n");
		y -= player.delta_y;
		x -= player.delta_x;
	}
	else if (keycode == 100 || keycode == 2){
		printf("D tuşuna basıldı.\n");
		player.alpha += 0.1;
		if (player.alpha > 2*PI){
			player.alpha -= 2*PI;
		}
		player.delta_x = cos(player.alpha)*5;
		player.delta_y = sin(player.alpha)*5;
	}
	else if (keycode == 97 || keycode == 0){
		printf("A tuşuna basıldı.\n");
		player.alpha -= 0.1;
		if (player.alpha < 0){
			player.alpha += 2*PI;
		}
		player.delta_x = cos(player.alpha)*5;
		player.delta_y = sin(player.alpha)*5;
	}
	else if (keycode == 53 || keycode == 65307){
		printf("ESC tuşuna basıldı.\n");
		shutdown(&data);
	}
	if (keycode == 65361 || keycode == 123){ // sol
		printf("<= tuşuna basıldı.\n");
		player.alpha -= 0.1;
		if (player.alpha < 0){
			player.alpha += 2*PI;
		}
		player.delta_x = cos(player.alpha);
		player.delta_y = sin(player.alpha);
	}
	else if (keycode == 65363 || keycode == 124){ // sağ
		printf("=> tuşuna basıldı.\n");
		player.alpha += 0.1;
		if (player.alpha > 2*PI){
			player.alpha -= 2*PI;
		}
		player.delta_x = cos(player.alpha);
		player.delta_y = sin(player.alpha);
	}
	map_init(x, y);
	return (0);
}


void my_mlx_pixel_put(int x, int y, int color){
	char *dst = image.buffer + (y * image.size_line + x * (image.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void put_image(int begin_x, int begin_y, int end_x, int end_y, int color){
	for (int y = begin_y; y < end_y; y++)
	for (int x = begin_x; x < end_x; x++)
	{
		my_mlx_pixel_put(x, y, color);
	}
	
}

void move(int x, int y){
	// if (map[image.calc_x(x) / 128 + (image.calc_y(y) * 6)] == 1){
	// 	printf("ok\n");
	// 	return;
	// }
	put_image(player.x, player.y, x, y, RED);
	player.x = x; player.y;
}

void draw(int beginX, int beginY, int endX, int endY, int color){
	double deltaX = endX - beginX;
	double deltaY = endY - beginY;
	int pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	deltaX /= pixels; // 1
	deltaY /= pixels; 	 
	double pixelX = beginX;
	double pixelY = beginY;
	while (pixels)
	{
		my_mlx_pixel_put(pixelX, pixelY, color);
		pixelX += deltaX;
		pixelY += deltaY;
		--pixels;
	}
}
int abs(int n) { return ((n > 0) ? n : (n * (-1))); }

// DDA Function for line generation
void DDA(int X0, int Y0, int X1, int Y1, int color)
{
    // calculate dx & dy
    int dx = X1 - X0;
    int dy = Y1 - Y0;
 
    // calculate steps required for generating pixels
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
 
    // calculate increment in x & y for each steps
    float Xinc = dx / (float)steps;
    float Yinc = dy / (float)steps;
 
    // Put pixel for each step
    float X = X0;
    float Y = Y0;
    for (int i = 0; i <= steps; i++) {
        my_mlx_pixel_put(round(X), round(Y), color); // put pixel at (X,Y)
        X += Xinc; // increment in x at each step
        Y += Yinc; // increment in y at each step // for visualization of line-       // generation step by step
    }
}

void put_apect(){
	float begin_x = player.x;
	float begin_y = player.y;
	float end_x;
	float end_y;
	float m_0 = abs(begin_x - end_x);
	float m_1 = abs(begin_y - end_y);
	player.diagonal = pow(data.width, 2) + pow(data.height, 2);
	player.diagonal = sqrt(player.diagonal);
	player.m = m_0 >= m_1 ? m_0 / m_1 : m_1 / m_0;
	for (size_t i = 1; i < 10000; i++)
	{
		end_x = player.x + (player.delta_x * i);
		end_y = player.y + (player.delta_y * i);
		int index = ((int)end_x / 128) + (((int)end_y / 128) * 6);
		if (map[index] == 1){
			printf("index:%d, x:%f, y:%f\n", index, (end_x / 128), ((end_y / 128) * 6));
			break;
		}
	}
	DDA(begin_x, begin_y, end_x, end_y, GREEN);
	printf("begin_x: %f, begin_y: %f, end_x: %f, end_y: %f, m:%f\n", begin_x, begin_y, end_x, end_y, player.m);
	// printf("%d:%d\n", end_wall_x(begin_x, begin_y), end_wall_y(begin_x, begin_y));
}

void map_init(int x, int y){
	int i = 0;

	if (map[(x / 128) + ((y / 128) * 6)] == 1){
		return;
	}
	mlx_clear_window(data.mlx, data.win);
	while(i < data.size)
	{
		if (map[i] == 1){
			put_image(image.calc_x(i), image.calc_y(i), image.calc_x(i) + data.units, image.calc_y(i) + data.units, LILAC);
		}else{
			put_image(image.calc_x(i), image.calc_y(i), image.calc_x(i) + data.units, image.calc_y(i) + data.units, WHITE);
		}
		put_image(image.calc_x(i), image.calc_y(i), image.calc_x(i) + data.units, image.calc_y(i) + 3, BLACK);
		put_image(image.calc_x(i), image.calc_y(i), image.calc_x(i) + 3, image.calc_y(i) + data.units, BLACK);
		i++;
	}
	printf("x: %d, y: %d\n", x, y);
	printf("delta_x:%f, delta_y:%f\n", player.delta_x, player.delta_y);
	// put_image(x, y, x + player.size, y + player.size, RED);
	player.x = x; player.y = y;
	put_apect();
	printf("%d\n", i);
	mlx_put_image_to_window(data.mlx, data.win, image.image, 0, 0);
}

int player_loca(){
	for (size_t i = 0; i < data.size; i++)
	{
		if (map[i] == -1) return (i);
	}	
	return (0);
}

int main(){
	init_data();
	map_init(image.calc_x(player_loca()), image.calc_y(player_loca()));
	mlx_hook(data.win, 2, 1L << 0, keyboard, &data);
	mlx_hook(data.win, 17, 0, shutdown, &data);	
	// exit(1);
	mlx_loop(data.mlx);
}