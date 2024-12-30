
#include "includes/cub3d.h"


static int	close_win(t_cub *data)
{
	mlx_destroy_window(data->mlx->mlx, data->mlx->win);
	free(data);
	exit(1);
}

static int	ft_hook_key(int key, t_cub *data)
{
	
	if (key == key_ESC)
		close_win(data);
	if (key == key_A || key == key_LEFT)
	{
		move(data, 0, -1);
		render_map(data, data->map);
		// double oldDirX = dirX;
		// dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
		// dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
		// double oldPlaneX = planeX;
		// planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
		// planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
	}
	if (key == key_S || key == key_DOWN)
	{
		move(data, 1, 0);
		render_map(data, data->map);
		// if(worldMap[int(posX - dirX * moveSpeed)][int(posY)] == false) posX -= dirX * moveSpeed;
    	// if(worldMap[int(posX)][int(posY - dirY * moveSpeed)] == false) posY -= dirY * moveSpeed;
	}
	if (key == key_D || key == key_RIGHT)
	{
		move(data, 0, 1);
		render_map(data, data->map);
		// double oldDirX = dirX;
		// dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
		// dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
		// double oldPlaneX = planeX;
		// planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
		// planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
	}
	if (key == key_W || key == key_UP)
	{
		move(data, -1, 0);
		render_map(data, data->map);
		// if(worldMap[int(posX + dirX * moveSpeed)][int(posY)] == false) posX += dirX * moveSpeed;
      	// if(worldMap[int(posX)][int(posY + dirY * moveSpeed)] == false) posY += dirY * moveSpeed;
	}
	// ray(data);
	/* printf("jugador x->%f, y->%f\n", data->player->x, data->player->y); */
	return (0);
}

void init_mlx(t_cub *cub)
{
	t_mlx	*mlx;

	// data = malloc(sizeof(t_cub));
	// maps = malloc(sizeof(t_map));
	// data->map = maps;
	// maps->map1d = map;
	// res = ft_split(maps->map1d, '\n');
	// maps->map = res;
	// data->steps = 3; //velocidad de avance
	// data->sp_spin =3 *(3.14/180); //velocidad de giro
	// cube_init(data);
	cub->mlx->mlx = mlx_init();
	mlx = cub->mlx;
	// printf("x-> %d y y-> %d.\n",data->x_max, data->y_max );
	mlx->win = mlx_new_window(mlx->mlx, WIN_WIDTH, WIN_HEIGHT, "prueba");
	init_minimap(cub);
	// data->count = 0;
	
	render_map(cub, cub->map);
	mlx_key_hook(mlx->win, ft_hook_key, cub);
	// mlx_pixel_put(data->mlx, data->win, data->player->x, data->player->y, 0x00FF24);
	// mlx_string_put(data->mlx, data->win, data->player->x, data->player->y, 0x00FF24, "Total steps");
	mlx_hook(mlx->win, 17, 0, close_win, cub);
	//mlx_loop_hook(data->mlx, del, data);  //añadir para efectos 
	mlx_loop(mlx->mlx);
}
