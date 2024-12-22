
#include "includes/cub3d.h"


static int	close_win(t_cub *data)
{
	mlx_destroy_window(data->mlx->mlx, data->mlx->win);
	printf("FINISH GAME\n");
	free_cub(data);
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

// static void cube_init(t_cub *data)
// {
// 	t_player *player;
	// double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane

	// double time = 0; //time of current frame
	// double oldTime = 0; //time of previous frame

	// data->map->size = 128; // cada cuadrado, centro seria 64x64
	// data->map->cols = 10 * data->map->size; //10 x 128 
	// data->map->rows = data->map->cols;
	
	// player = malloc(sizeof(t_player));
	// player->x = (5 * data->size) + (data->size / 2);
	// player->y = (8 * data->size) + (data->size / 2);
	// player->a = 0;
	/* player->x = 2.0;
	player->y = 8.0; */
	// player->dirX = 2.0; //ahora mismo apunta para abajo x5 y0
	// player->dirY = 0.0;
	// data->player = player;
	// positionPlayer(data);
	// printf("jugador x->%f, y->%f\n", data->player->x, data->player->y);
	

	// oldTime = time;
    // time = getTicks();
    // double frameTime = (time - oldTime) / 1000.0; //frameTime is the time this frame has taken, in seconds
    // print(1.0 / frameTime); //FPS counter
    // redraw();
    // cls();

    //speed modifiers
    // double moveSpeed = frameTime * 5.0; //the constant value is in squares/second
    // double rotSpeed = frameTime * 3.0; //the constant value is in radians/second
// }

// int	del_data(t_cub *data)
// {
// 	data->count++;
// 	if (data->count % 10000 == 0)
// 	{
// 		data->count = 0;
// 		print_map(data, data->map);
// 	}
// 	return (0);
// }

void init_mlx(t_cub *cub)
{
	t_mlx	*mlx_main;

	mlx_main = malloc(sizeof(t_mlx));
	// maps = malloc(sizeof(t_map));
	// data->map = maps;
	// maps->map1d = map;
	// res = ft_split(maps->map1d, '\n');
	// maps->map = res;
	// data->steps = 3; //velocidad de avance
	// data->sp_spin =3 *(3.14/180); //velocidad de giro
	// cube_init(data);
	cub->mlx = mlx_main;
	mlx_main->mlx = mlx_init();
	// printf("x-> %d y y-> %d.\n",data->x_max, data->y_max );
	mlx_main->win = mlx_new_window(mlx_main->mlx, WIN_WIDTH, WIN_HEIGHT, "prueba");
	init_minimap(cub);
	// data->count = 0;
	
	render_map(cub, cub->map);
	mlx_key_hook(mlx_main->win, ft_hook_key, cub);
	// mlx_pixel_put(data->mlx, data->win, data->player->x, data->player->y, 0x00FF24);
	// mlx_string_put(data->mlx, data->win, data->player->x, data->player->y, 0x00FF24, "Total steps");
	mlx_hook(mlx_main->win, 17, 0, close_win, cub);
	//mlx_loop_hook(data->mlx, del, data);  //añadir para efectos 
	mlx_loop(mlx_main->mlx);
}

// int	main(int argc, char *argv[])
// {
// 	char *map;

// 	if(argc > 3)
// 	{
// 		printf("Error de parametros\n");
// 		return (0);
// 	}
// 	printf("en el programa con -> %s\n", argv[1]);
// 	map = read_map(argv[1]);
// 	if (map == NULL)
// 	{
// 		write(1, "ERROR\n", 6);
// 		return (0);
// 	}
// 	cube(map);
// 	return (1);
// }

