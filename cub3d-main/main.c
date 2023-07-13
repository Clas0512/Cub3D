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
# define GRAY	0x726E6E

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
struct s_image img;

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

struct s_raycast_wall{
	int x;
	int y;
	float ray_len;
};

struct s_raycast_wall raycast[768];


int map[] = {
	1, 1, 1, 1, 1, 1,
	1, 0, 1, 0, 0, 1,
	1, 0, 0, 0, 1, 1,
	1, 0, 1, 0, 0, 1,
	1, 0, 0, -1, 0, 1,
	1, 0, 0, 0, 0, 1,
	1, 0, 0, 1, 0, 1,
	1, 1, 1, 1, 1, 1,	
};

void move(int x, int y);
void map_init(int x, int y);
void map_init_3D(int x, int y, struct s_image img);

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
	data.win = mlx_new_window(data.mlx, data.width*2, data.height, "hi");
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
		y += (int)player.delta_y*2;
		x += (int)player.delta_x*2;
	}
	else if (keycode == 115 || keycode == 1){
		printf("S tuşuna basıldı.\n");
		x -= (int)player.delta_x*2;
		y -= (int)player.delta_y*2;
	}
	else if (keycode == 100 || keycode == 2 || keycode == 65363 || keycode == 124){
		printf("D tuşuna basıldı.\n");
		player.alpha += 0.1;
		if (player.alpha > 2*PI){
			player.alpha -= 2*PI;
		}
		player.delta_x = cos(player.alpha)*5;
		player.delta_y = sin(player.alpha)*5;
	}
	else if (keycode == 97 || keycode == 0 || keycode == 65361 || keycode == 123){
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
	map_init(x, y);
	map_init_3D(x, y, img);
	return (0);
}


void my_mlx_pixel_put(int x, int y, int color, struct s_image img){
	char *dst = img.buffer + (y * img.size_line + x * (img.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void put_image(int begin_x, int begin_y, int end_x, int end_y, int color, struct s_image img){
	for (int y = begin_y; y < end_y; y++)
	for (int x = begin_x; x < end_x; x++)
		my_mlx_pixel_put(x, y, color, img);
}

void draw(int beginX, int beginY, int endX, int endY, int color){
	double deltaX = endX - beginX;
	double deltaY = endY - beginY;
	int pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	deltaX /= pixels;
	deltaY /= pixels; 	 
	double pixelX = beginX;
	double pixelY = beginY;
	while (pixels)
	{
		my_mlx_pixel_put(pixelX, pixelY, color, image);
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
        my_mlx_pixel_put(round(X), round(Y), color, image); // put pixel at (X,Y)
        X += Xinc; // increment in x at each step
        Y += Yinc; // increment in y at each step // for visualization of line-       // generation step by step
    }
}

void put_apect(){
	float begin_x = player.x;
	float begin_y = player.y;
	float dx = player.delta_x;
	float dy = player.delta_y;
	float end_x = begin_x + dx * 20;
	float end_y = begin_y + dy * 20;
	float newo = player.alpha;
	newo -= 384 * 0.0174533 / 12;
	if (newo < 0){
		newo += 2*PI;
	}
	dx = cos(newo);
	dy = sin(newo);
	for (size_t j = 0; j < 768; j++)
	{
		for (size_t i = 1; i < 10000; i++)
		{
			end_x = player.x + (dx * i);
			end_y = player.y + (dy * i);
			int index = ((int)end_x / 128) + (((int)end_y / 128) * 6);
			if (map[index] == 1){
				printf("index:%d, x:%f, y:%f\n", index, (end_x / 128), ((end_y / 128) * 6));
				break;
			}
		}
		raycast[j].x = end_x;
		raycast[j].y = end_y;
		raycast[j].ray_len = sqrt(pow(fabs(end_x - begin_x), 2) + pow(fabs(end_y - begin_y), 2));
		if (j < 392 && j > 376)
			DDA(begin_x, begin_y, end_x, end_y, BLACK);
		else
			DDA(begin_x, begin_y, end_x, end_y, GREEN);
		newo += 0.0174533 / 12;
		dx = cos(newo);
		dy = sin(newo);
	}
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
			put_image(image.calc_x(i), image.calc_y(i), image.calc_x(i) + data.units, image.calc_y(i) + data.units, LILAC, image);
		}else{
			put_image(image.calc_x(i), image.calc_y(i), image.calc_x(i) + data.units, image.calc_y(i) + data.units, WHITE, image);
		}
		put_image(image.calc_x(i), image.calc_y(i), image.calc_x(i) + data.units, image.calc_y(i) + 3, BLACK, image);
		put_image(image.calc_x(i), image.calc_y(i), image.calc_x(i) + 3, image.calc_y(i) + data.units, BLACK, image);
		i++;
	}
	printf("x: %d, y: %d\n", x, y);
	printf("delta_x:%f, delta_y:%f\n", player.delta_x, player.delta_y);
	// put_image(x, y, x + player.size, y + player.size, RED);
	player.x = x; player.y = y;
	put_apect();
	printf("%d\n", i);
	// mlx_put_image_to_window(data.mlx, data.win, image.image, 0, 0);
}

float calc_ratio(float ray_len)
{
	float wall_len;

	wall_len = data.height * 20 / ray_len;
	if (wall_len > data.height)
		return(data.height);
	return (wall_len);
}

void put_wall(int x, int y, struct s_image img)
{
	printf("x:%d, y:%d\n",x,y);
	int height = data.height / 2;
	int width = data.width;
	int xx;
	int yy;
	// int j = width;
	for (size_t i = 0; i < 768; i++)
	{
		// printf("RAY_LEN : '%f'\n", raycast[i].ray_len);
		yy = (int)calc_ratio(raycast[i].ray_len);
		printf("yy:%d\n", yy);
		put_image(width, height - (yy / 2), width + (width / 768), height + (yy / 2), BLACK, img);
		width += data.width / 768;
	}
}

void map_init_3D(int x, int y, struct s_image img){
	printf("ZORT\n");
	int i = 0;
	put_image(x, 0, x + data.width, data.height / 2, GRAY, img);
	put_image(data.width, data.height / 2, data.width + data.width - 1 , data.height - 1, GREEN, img);
	printf("--------- ZOOOOOOOOORT ---------\n");
	// printf("x:%d, y:%d\n", x, y);
	put_wall(x, y, img);
	// put_wall(x, y, img);
	// put_image(x - (data.units / 2), y + (data.units / 2), x + (data.units / 2), y + (data.units / 2) * 2, RED, img);
	mlx_put_image_to_window(data.mlx, data.win, img.image, 0, 0);
}

int player_loca()
{
	for (size_t i = 0; i < data.size; i++)
	{
		if (map[i] == -1) return (i);
	}	
	return (0);
}

int main(){
	init_data();
	img.image = mlx_new_image(data.mlx, data.width, data.height);
	img.buffer = mlx_get_data_addr(img.image, &(img.bits_per_pixel), &(img.size_line), &(img.endian));
	img.calc_x = &calc_x;
	img.calc_y = &calc_y;
	map_init(image.calc_x(player_loca()) + 5, image.calc_y(player_loca()) + 5);
	map_init_3D(data.width, data.height, img);
	mlx_hook(data.win, 2, 1L << 0, keyboard, &data);
	mlx_hook(data.win, 17, 0, shutdown, &data);	
	// exit(1);
	mlx_loop(data.mlx);
}