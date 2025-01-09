
#include "includes/cub3d.h"


static int	close_win(t_cub *data)
{
	mlx_destroy_window(data->mlx->mlx_ptr, data->mlx->win);
	printf("FINISH GAME\n");
	free_cub(data);
	exit(1);
}

static int	key_press(int key, t_cub *cub)
{
	t_player *player;

	player = cub->map->player;
	if (key == KEY_ESC)
		close_win(cub);
	//move
	if (key == KEY_A) //move left
	{
		player->walk[0] = 0; //TODO: this should have sin/cos of angle
		player->walk[1] = -1;
		// move(cub, 0, -1);
	}
	if (key == KEY_S)
	{
		player->walk[0] = 1;
		player->walk[1] = 0;
		// move(cub, 1, 0);
	}
	if (key == KEY_D)
	{
		player->walk[0] = 0;
		player->walk[1] = 1;
		// move(cub, 0, 1);
	}
	if (key == KEY_W)
	{
		player->walk[0] = -1;
		player->walk[1] = 0;
		// move(cub, -1, 0);
	}
	//TODO: rotation, review move to add sin/cos of angle
	return (0);
}

static int render_loop(t_cub *cub)
{	
	//move settings? to recalculate after key_press
	print_player(cub);

	// move(cub);
	//RENDER/DRAW everything
	render(cub, cub->map);
	//RAYCASTING
	// ray(cub);
	return (0);
} 

int init_engine(t_cub *cub)
{
	t_mlx	*mlx;

	mlx = cub->mlx;
	mlx_key_hook(mlx->win, key_press, cub);
	mlx_hook(mlx->win, 17, 0, close_win, cub);
	mlx_loop_hook(mlx->mlx_ptr, render_loop, cub);
	mlx_loop(mlx->mlx_ptr);
	return (0);
}

int init_mlx(t_cub *cub)
{
	t_mlx	*mlx;

	cub->mlx = ft_calloc(1, sizeof(t_mlx));
	if (!cub->mlx)
		return (print_error("init_mlx", NULL));
	mlx = cub->mlx;
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
		return (print_error("init-mlx", NULL));
	// printf("x-> %d y y-> %d.\n",data->x_max, data->y_max );
	mlx->win = mlx_new_window(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "main-window");
	if (!mlx->win)
		return (print_error("init-mlx", NULL));
	mlx->img = mlx_new_image(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (!mlx->img)
		return (print_error("init-mlx", NULL));
	mlx->img_addr = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->line_len,
			&mlx->endian);
	if (!mlx->img_addr)
		return (print_error("init-mlx", NULL));
	return (0);
}
