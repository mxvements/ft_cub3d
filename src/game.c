
#include "includes/cub3d_game.h"


static int	close_win(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	free(data);
	exit(1);
}

static void move(t_data *data, int x, int y)
{
	data->player->x += x;
	data->player->y += y;
}

static int	ft_hook_key(int key, t_data *data)
{
	if (key == key_ESC)
		close_win(data);
	if (key == key_A || key == key_LEFT)
	{
		move(data, 1, 0);
		// double oldDirX = dirX;
		// dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
		// dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
		// double oldPlaneX = planeX;
		// planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
		// planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
	}
	if (key == key_S || key == key_DOWN)
	{
		// if(worldMap[int(posX - dirX * moveSpeed)][int(posY)] == false) posX -= dirX * moveSpeed;
    	// if(worldMap[int(posX)][int(posY - dirY * moveSpeed)] == false) posY -= dirY * moveSpeed;
	}
	if (key == key_D || key == key_RIGHT)
	{
		// double oldDirX = dirX;
		// dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
		// dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
		// double oldPlaneX = planeX;
		// planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
		// planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
	}
	if (key == key_W || key == key_UP)
	{
		// if(worldMap[int(posX + dirX * moveSpeed)][int(posY)] == false) posX += dirX * moveSpeed;
      	// if(worldMap[int(posX)][int(posY + dirY * moveSpeed)] == false) posY += dirY * moveSpeed;
	}
	// printf("teclado -> %i \n",key);
	return (0);
}

char	*read_map(char *s)
{
	int		fd;
	char	*res;
	int		count;
	char	buffer[101];

	res = "\n";
	fd = open(s, O_RDONLY);
	if (fd < 0)
		return (NULL);
	count = read(fd, buffer, 100);
	while (count != 0)
	{
		if (count == -1)
			return (NULL);
		buffer[count] = '\0';
		res = ft_strjoin(res, buffer); //TODO hablar con lucia para ver la funcion que libera la memoria
		count = read(fd, buffer, 100);
	}
	return (close(fd), res);
}

static void cube_init(t_data *data)
{
	t_player *player;
	// double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane

	// double time = 0; //time of current frame
	// double oldTime = 0; //time of previous frame

	data->size = 128; // cada cuadrado, centro seria 64x64
	data->x_max = 10 * data->size; //10 x 64
	data->y_max = data->x_max;
	
	player = malloc(sizeof(t_player));
	// player->x = (5 * data->size) + (data->size / 2);
	// player->y = (8 * data->size) + (data->size / 2);
	// player->a = 0;
	// int mapa[10][10];
	// int mapa[data->x_max][data->y_max] = {
	// 	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	// 	{1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
	// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	// 	{1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
	// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	// 	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	// };
	// data->map->map2d = mapa;
	player->x = .0;
	player->y = 8.0;
	player->dirX = 1.0;
	player->dirY = 0.0;
	data->player = player;
	

	// oldTime = time;
    // time = getTicks();
    // double frameTime = (time - oldTime) / 1000.0; //frameTime is the time this frame has taken, in seconds
    // print(1.0 / frameTime); //FPS counter
    // redraw();
    // cls();

    //speed modifiers
    // double moveSpeed = frameTime * 5.0; //the constant value is in squares/second
    // double rotSpeed = frameTime * 3.0; //the constant value is in radians/second
}

int	del_data(t_data *data)
{
	data->count++;
	if (data->count % 10000 == 0)
	{
		data->count = 0;
		print_map_game(data, data->map);
	}
	return (0);
}

static void cube(char *map)
{
	t_data		*data;
	t_map_game	*maps;
	char		**res;

	data = malloc(sizeof(t_data));
	maps = malloc(sizeof(t_map));
	data->map = maps;
	maps->map = map;
	res = ft_split(maps->map, '\n');
	maps->map2d = res;
	data->steps = 3; //velocidad de avance
	data->sp_spin =3 *(3.14/180); //velocidad de giro
	cube_init(data);
	ini(data);
	data->mlx = mlx_init();
	printf("x-> %d y y-> %d.\n",data->x_max, data->y_max );
	data->win = mlx_new_window(data->mlx, data->x_max, data->y_max, "prueba");
	data->count = 0;
	//ray(data);
	print_map_game(data, data->map);
	mlx_key_hook(data->win, ft_hook_key, data);
	// mlx_pixel_put(data->mlx, data->win, data->player->x, data->player->y, 0x00FF24);
	// mlx_string_put(data->mlx, data->win, data->player->x, data->player->y, 0x00FF24, "Total steps");
	mlx_hook(data->win, 17, 0, close_win, data);
	//mlx_loop_hook(data->mlx, del, data);  //añadir para efectos 
	mlx_loop(data->mlx);
}

int	main(int argc, char *argv[])
{
	char *map;

	if(argc > 3)
	{
		printf("Error de parametros\n");
		return (0);
	}
	printf("en el programa con -> %s\n", argv[1]);
	map = read_map(argv[1]);
	if (map == NULL)
	{
		write(1, "ERROR\n", 6);
		return (0);
	}
	cube(map);
	return (1);
}

