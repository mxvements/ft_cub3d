
#include "cub3d.h"

static void cube(void)
{
	void	*mlx_ptr;
	void	*win_ptr;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "prueba");
	mlx_pixel_put(mlx_ptr, win_ptr, 250, 250, 0xFFFFFFF);
	mlx_loop(mlx_ptr);
}

int	mian(int argc, char *argv[])
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

