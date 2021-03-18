
#include "cub3d.h"

void            my_mlx_pixel_put(t_data *data, int x, int y, unsigned int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void			ft_line(int i, int drawStart, int drawEnd, unsigned int color, t_param *p, t_data *img)
{
	while (drawStart < drawEnd)
	{
		my_mlx_pixel_put(img, i, drawStart, color);
		drawStart++;
	}
}

int worldMap[24][24]={
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


int  ft_changedir(int keycode, t_param *p)
{
if (keycode == W)
	{
      if(worldMap[(int)(p->posX + p->dirX * 0.25)][(int)(p->posY)] == 0) p->posX += p->dirX * 0.25;
      if(worldMap[(int)(p->posX)][(int)(p->posY + p->dirY * 0.25)] == 0) p->posY += p->dirY * 0.25;
	}
	else if (keycode == S)
	{
      if(worldMap[(int)(p->posX - p->dirX * 0.25)][(int)(p->posY)] == 0) 
      p->posX -= p->dirX * 0.25;
      if(worldMap[(int)(p->posX)][(int)(p->posY - p->dirY * 0.25)] == 0) 
      p->posY -= p->dirY * 0.25;
	}
	else if (keycode == A)
	{
		if(worldMap[(int)p->posX][(int)(p->posY + p->dirX * 0.25)] == 0)
			p->posY += p->dirX * 0.25;
		if(worldMap[(int)(p->posX - p->dirY * 0.25)][(int)p->dirY] == 0)
			p->posX -= p->dirY * 0.25;
	}
	else if (keycode == D)
	{
		if(worldMap[(int)p->dirX][(int)(p->posY - p->dirX * 0.25)] == 0)
			p->posY -= p->dirX * 0.25;
		if(worldMap[(int)p->dirY][(int)(p->posX + p->dirY * 0.25)] == 0)
			p->posX += p->dirY * 0.25;
	}
	else if (keycode == LEFT)
	{
      double oldDirX = p->dirX;
      p->dirX = p->dirX * cos(rotSpeed) - p->dirY * sin(rotSpeed);
      p->dirY = oldDirX * sin(rotSpeed) + p->dirY * cos(rotSpeed);
      double oldPlaneX = p->planeX;
      p->planeX = p->planeX * cos(rotSpeed) - p->planeY * sin(rotSpeed);
      p->planeY = oldPlaneX * sin(rotSpeed) + p->planeY * cos(rotSpeed);
    }
	else if (keycode == RIGHT)
	{
     double oldDirX = p->dirX;
      p->dirX = p->dirX * cos(-rotSpeed) - p->dirY * sin(-rotSpeed);
      p->dirY = oldDirX * sin(-rotSpeed) + p->dirY * cos(-rotSpeed);
      double oldPlaneX = p->planeX;
      p->planeX = p->planeX * cos(-rotSpeed) - p->planeY * sin(-rotSpeed);
      p->planeY = oldPlaneX * sin(-rotSpeed) + p->planeY * cos(-rotSpeed);
    }
	else if (keycode == ESC)
		exit(0);
	return (0);
}
int ft_render(t_param *p)
{
  int x = 0;
    int hit;
    t_data img;
    double perpWallDist;
  int side;
      img.img = mlx_new_image(p->mlx, screenWidth, screenHeight);
  img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
while (x < screenWidth)
  {
  p->camera = 2 * x / (double)screenWidth - 1 ;
  p->rayDirX = p->dirX + p->planeX * p->camera;
  p->rayDirY = p->dirY + p->planeY * p->camera;
	int mapX = (int)p->posX;
	int mapY = (int)p->posY;
  hit = 0;
  p->deltaDistX = fabs(1 / p->rayDirX);
  p->deltaDistY = fabs(1 / p->rayDirY);
  if (p->rayDirX < 0)
      {
        p->stepX = -1;
        p->sideDistX = (p->posX - mapX) * p->deltaDistX;
      }
      else
      {
        p->stepX = 1;
        p->sideDistX = (mapX + 1.0 - p->posX) * p->deltaDistX;
      }
      if (p->rayDirY < 0)
      {
        p->stepY = -1;
        p->sideDistY = (p->posY - mapY) * p->deltaDistY;
      }
      else
      {
        p->stepY = 1;
        p->sideDistY = (mapY + 1.0 - p->posY) * p->deltaDistY;
      }
      while (hit == 0)
      {
        if (p->sideDistX < p->sideDistY)
        {
          p->sideDistX += p->deltaDistX;
          mapX += p->stepX;
          side = 0;
        }
        else
        {
          p->sideDistY += p->deltaDistY;
          mapY += p->stepY;
          side = 1;
        }
        if (worldMap[mapX][mapY] > 0) 
        hit = 1;
      } 
      if (side == 0) 
        perpWallDist = (mapX - p->posX + (1 - p->stepX) / 2) / p->rayDirX;
      else          
        perpWallDist = (mapY - p->posY + (1 - p->stepY) / 2) / p->rayDirY;
			int lineHeight = (int)(screenHeight / perpWallDist);
			int drawStart = -lineHeight / 2 + screenHeight / 2;
			if(drawStart < 0)
				drawStart = 0;
			int drawEnd = lineHeight / 2 + screenHeight / 2;
			if(drawEnd >= screenHeight)
				drawEnd = screenHeight - 1;
			unsigned int color;
			if (p->posY > mapY && side)
				color = RED;
			else if (p->posY < mapY && side)
				color = BLUE;
			else if (p->posX > mapX && !side)
				color = WHITE;
			else if (p->posX < mapX && !side)
				color = GREEN;
			ft_line(x, drawStart, drawEnd, color, p, &img);
      x++;
		}
    mlx_put_image_to_window(p->mlx, p->win, img.img, 0, 0);
    return (0);
}
int main()
{
  t_param p;
  p.posX = 22;
  p.posY = 12;
  p.planeX = 0;
  p.planeY = 0.66;
  p.dirX = -1;
  p.dirY = 0;
  p.mlx = mlx_init();
  p.win = mlx_new_window(p.mlx, screenWidth, screenHeight, "cub3d");
  mlx_hook(p.win, X_EVENT_KEY_PRESS, 0, &ft_changedir, &p);
  mlx_loop_hook(p.mlx, &ft_render, &p);
      mlx_loop(p.mlx);
  }