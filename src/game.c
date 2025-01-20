
#include "includes/cub3d.h"

static void	change_move_speed(int keycode, t_cub *cub)
{
	const float	move_speed_diff = 0.01;

	if (keycode == KEY_F3) //-
	{
		cub->options.move_speed -= move_speed_diff;
		if (cub->options.move_speed <= 0)
			cub->options.move_speed = 0;
	}
	else if (keycode == KEY_F4) //+
	{
		cub->options.move_speed += move_speed_diff;
	}
	printf(GREEN "move speed changed to %f\n" RESET, cub->options.move_speed);
}

static void	change_rotate_speed(int keycode, t_cub *cub)
{
	const float	rotate_speed_diff = PI / 64;

	if (keycode == KEY_F5) //-
	{
		cub->options.rotate_speed -= rotate_speed_diff;
		if (cub->options.rotate_speed <= 0)
			cub->options.rotate_speed = 0;
	}
	else if (keycode == KEY_F6) //+
	{
		cub->options.rotate_speed += rotate_speed_diff;
	}
	printf(GREEN "rotate speed changed to %f\n" RESET,
		cub->options.rotate_speed);
}

static int	close_win(t_cub *data)
{
	mlx_destroy_window(data->mlx->mlx_ptr, data->mlx->win);
	printf("FINISH GAME\n");
	free_cub(data);
	exit(1);
}

static int	print_key_options(t_cub *cub)
{
	(void)cub;
	printf(LGREEN "\n[CUB3D OPTIONS]\n" RESET);
	printf(LGREEN "+ Change options status with the following keys:\n" RESET);
	printf(LGREEN "  +  show status on console\t (space tab)\n" RESET);
	printf(LGREEN "  +  show game info on console\t (i)\n" RESET);
	printf(LGREEN "  +  wall collisions\t\t (F1)\n" RESET);
	printf(LGREEN "  +  show/hide minimap\t\t (F2)\n" RESET);
	printf(LGREEN "  +  move speed\t\t\t (F3/F4 -/+)\n" RESET);
	printf(LGREEN "  +  rotate speed\t\t (F5/F6 -/+)\n" RESET);
	printf("\n");
	return (0);
}

static int	key_press(int keycode, t_cub *cub)
{
	t_player	*player;

	player = cub->map->player;
	if (keycode == KEY_W)
		player->move_keys.key_up = 1;
	if (keycode == KEY_A)
		player->move_keys.key_left = 1;
	if (keycode == KEY_S)
		player->move_keys.key_down = 1;
	if (keycode == KEY_D)
		player->move_keys.key_right = 1;
	if (keycode == KEY_LEFT)
		player->move_keys.left_rotate = 1;
	if (keycode == KEY_RIGHT)
		player->move_keys.right_rotate = 1;
	if (keycode == KEY_ESC)
		close_win(cub);
	return (0);
}

static int	key_release(int keycode, t_cub *cub)
{
	t_player	*player;

	player = cub->map->player;
	if (keycode == KEY_W)
		player->move_keys.key_up = 0;
	if (keycode == KEY_A)
		player->move_keys.key_left = 0;
	if (keycode == KEY_S)
		player->move_keys.key_down = 0;
	if (keycode == KEY_D)
		player->move_keys.key_right = 0;
	if (keycode == KEY_LEFT)
		player->move_keys.left_rotate = 0;
	if (keycode == KEY_RIGHT)
		player->move_keys.right_rotate = 0;
	if (keycode == KEY_ESC)
		close_win(cub);
	if (keycode == KEY_O)
		print_key_options(cub);
	if (keycode == KEY_i)
		print_cub(cub);
	if (keycode == KEY_SP)
		print_options_status(&cub->options);
	if (keycode == KEY_F3 || keycode == KEY_F4)
		change_move_speed(keycode, cub);
	if (keycode == KEY_F5 || keycode == KEY_F6)
		change_rotate_speed(keycode, cub);
	return (0);
}
// TODO: change to while
static void	clean_img(t_cub *cub)
{
	for (int i = 0; i < WIN_HEIGHT; i++)
		for (int j = 0; j < WIN_WIDTH; j++)
			put_pixel(j, i, 0x00, cub);
}

static int	render_loop(t_cub *cub)
{
	t_mlx	*mlx;

	mlx = cub->mlx;
	// move settings? to recalculate after key_press
	clean_img(cub);
	move_and_rotate(cub);
	// RENDER/DRAW everything
	render(cub, cub->map);
	put_camera(cub);
	minimap_put_player(cub, 0xFF0000);
	minimap_put_axis(cub, 0xFF0000);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, mlx->img, 0, 0);
	minimap_put_str(cub);
	// RAYCASTING
	// ray(cub);
	return (0);
}

int	init_engine(t_cub *cub)
{
	t_mlx	*mlx;

	mlx = cub->mlx;
	mlx_hook(mlx->win, 2, 1L << 0, key_press, cub);
	mlx_hook(mlx->win, 3, 1L << 1, key_release, cub);
	mlx_hook(mlx->win, 17, 0, close_win, cub);
	mlx_loop_hook(mlx->mlx_ptr, render_loop, cub);
	mlx_loop(mlx->mlx_ptr);
	return (0);
}

int	init_mlx(t_cub *cub)
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
	mlx->win = mlx_new_window(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "cub3d");
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
