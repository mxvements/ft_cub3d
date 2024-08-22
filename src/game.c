
#include "cub3d.h"


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
		move(data, 0, -1);
	}
	if (key == key_S || key == key_DOWN)
	{
		move(data, 1, 0);
	}
	if (key == key_D || key == key_RIGHT)
	{
		move(data, 0, 1);
	}
	if (key == key_W || key == key_UP)
	{
		move(data, -1, 0);
	}
	// printf("teclado -> %i \n",key);
	return (0);
}


static void cube_init(t_data *data)
{
	t_player *player;

	data->size = 128; // cada cuadrado, centro seria 64x64
	data->x_max = 1280; //10 x128
	data->y_max = data->x_max;
	
	player = malloc(sizeof(t_player));
	player->x = (5 * data->size) + (data->size / 2);
	player->y = (8 * data->size) + (data->size / 2);
	player->a = 0;
	data->player = player;
}

static void cube(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	cube_init(data);
	data->steps = 3; //velocidad de avance
	data->sp_spin =3 *(3.14/180); //velocidad de giro
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->x_max, data->y_max, "prueba");
	mlx_key_hook(data->win, ft_hook_key, data);
	// mlx_pixel_put(data->mlx, data->win, data->player->x, data->player->y, 0x00FF24);
	mlx_string_put(data->mlx, data->win, data->player->x, data->player->y, 0x00FF24, "Total steps");
	mlx_loop(data->mlx);
}

int	main(int argc, char *argv[])
{
	if(argc > 3)
	{
		printf("Error de parametros\n");
		return (0);
	}
	printf("en el programa con -> %s\n", argv[1]);
	cube();
	return (1);
}

