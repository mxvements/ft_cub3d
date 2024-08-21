
#include "cub3d.h"


static int	close_win(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	free(data);
	exit(1);
}

static int	ft_hook_key(int key, t_data *data)
{
	if (key == key_ESC)
		close_win(data);
	// if (key == key_A || key == key_LEFT)
	// {
	// 	move(mlx, 0, -1);
	// }
	// if (key == key_S || key == key_DOWN)
	// {
	// 	move(mlx, 1, 0);
	// }
	// if (key == key_D || key == key_RIGHT)
	// {
	// 	move(mlx, 0, 1);
	// }
	// if (key == key_W || key == key_UP)
	// {
	// 	move(mlx, -1, 0);
	// }
	// printf("teclado -> %i \n",key);
	return (0);
}

static void cube(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	data->x_max = 1500;
	data->y_max = data->x_max;
	data->steps = 3; //velocidad de avance
	data->sp_spin =3 *(3.14/180); //velocidad de giro
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->x_max, data->y_max, "prueba");

	mlx_key_hook(data->win, ft_hook_key, data);
	// mlx_pixel_put(data->mlx, data->win, 250, 250, 0xF7DC6F);
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

