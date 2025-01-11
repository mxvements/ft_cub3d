
#include "includes/cub3d.h"

static int	close_win(t_cub *data)
{
	mlx_destroy_window(data->mlx->mlx_ptr, data->mlx->win);
	printf("FINISH GAME\n");
	free_cub(data);
	exit(1);
}



// static int	key_touch(int keycode, t_cub *cub)
// {
// 	t_player *player;
// 	player = cub->map->player;
// 	if (keycode == KEY_ESC)
// 		close_win(cub);
// 	// //move
// 	// if (key == KEY_A) //move left
// 	// {
// 	// 	player->walk[0] = 0; //TODO: this should have sin/cos of angle
// 	// 	player->walk[1] = -1;
// 	// 	// move(cub, 0, -1);
// 	// }
// 	// if (key == KEY_S)
// 	// {
// 	// 	player->walk[0] = 1;
// 	// 	player->walk[1] = 0;
// 	// 	// move(cub, 1, 0);
// 	// }
// 	// if (key == KEY_D)
// 	// {
// 	// 	player->walk[0] = 0;
// 	// 	player->walk[1] = 1;
// 	// 	// move(cub, 0, 1);
// 	// }
// 	// if (key == KEY_W)
// 	// {
// 	// 	player->walk[0] = -1;
// 	// 	player->walk[1] = 0;
// 	// 	// move(cub, -1, 0);
// 	// }
// 	// //TODO: rotation, review move to add sin/cos of angle
// 	return (0);
// }

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
	return (0);
}
static void	clean_img(t_cub *game)
{
	for (int i = 0; i < WIN_HEIGHT; i++)
		for (int j = 0; j < WIN_WIDTH; j++)
			put_pixel(j, i, 0x00, game);
}

static int	render_loop(t_cub *cub)
{
	// move settings? to recalculate after key_press
	clean_img(cub);
	move(cub);
	// RENDER/DRAW everything
	render(cub, cub->map);
	put_axis(cub, 0xFF0000);
	mlx_put_image_to_window(cub->mlx->mlx_ptr, cub->mlx->win, cub->mlx->img,0, 0);
	// RAYCASTING
	// ray(cub);
	return (0);
}

int	init_engine(t_cub *cub)
{
	t_mlx	*mlx;

	mlx = cub->mlx;
	// mlx_key_hook(mlx->win, key_touch, cub);
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
	mlx->win = mlx_new_window(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT,
			"main-window");
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
