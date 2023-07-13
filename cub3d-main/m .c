#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "mlx/mlx.h"


#define mapWidth 24
#define mapHeight 24
#define screenWidth mapWidth * 64
#define screenHeight mapHeight * 64
# define GREEN	0x25bc17
# define WHITE	0xffffff
# define RED	0XF51313
# define LILAC	0x8C1DEE
# define BLACK	0x000000

struct s_data{
	void *mlx;
	void *win;
	void *image;
	char *buffer;
} data;

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};
int bits_pixel, size_line, endian; // image addrs

void my_mlx_pixel_put(int x, int y, int color){
	char *dst = data.buffer + (y * size_line + x * (bits_pixel / 8));
	*(unsigned int*)dst = color;
}

void put_image(int begin_x, int begin_y, int end_x, int end_y, int color){
	for (int y = begin_y; y < end_y; y++)
	for (int x = begin_x; x < end_x; x++)
	{
		my_mlx_pixel_put(x, y, color);
	}
}

void map_init(){
	for (size_t i = 0; worldMap[i]; i++){
		for (size_t k = 0; worldMap[i][k]; k++)
		{
			if (worldMap[i][k] != 0){
				put_image(i * 64, k * 64, i * 64 + 64, k * 64 + 64, LILAC);
			}else{
				put_image(i * 64, k * 64, i * 64 + 64, k * 64 + 64,WHITE);
			}
		}
	}
	
}

int main(){
	float posX = 22, posY = 12;  //x and y start position
	float dirX = -1, dirY = 0; //initial direction vector
	float planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane
	float time = 0; //time of current frame
	float oldTime = 0; //time of previous frame
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, screenWidth, screenWidth, "Raycasting");
	data.image = mlx_new_image(data.mlx, screenWidth, screenHeight);
	data.buffer = mlx_get_data_addr(data.image, &bits_pixel, &size_line, &endian);
	map_init();
	mlx_put_image_to_window(data.mlx, data.win, data.image, 0, 0);
	mlx_loop(data.mlx);
}