#include "../includes/cub3d.h"

static void	change_move_speed(int keycode, t_cub *cub)
{
	const float	move_speed_diff = 0.01;

	if (keycode == KEY_F3)
	{
		if (cub->options.move_speed <= 0.001f)
			return ;
		cub->options.move_speed -= move_speed_diff;
	}
	else if (keycode == KEY_F4)
	{
		if (cub->options.move_speed >= MOVE_MAX)
			return ;
		cub->options.move_speed += move_speed_diff;
	}
	printf(GREEN "move speed changed to %f\n" RESET, cub->options.move_speed);
}

static void	change_rotate_speed(int keycode, t_cub *cub)
{
	const float	rotate_speed_diff = PI / 64;

	if (keycode == KEY_F5)
	{
		if (cub->options.rotate_speed <= 0.001f)
			return ;
		cub->options.rotate_speed -= rotate_speed_diff;
	}
	else if (keycode == KEY_F6)
	{
		if (cub->options.rotate_speed >= PI * 2)
			return ;
		cub->options.rotate_speed += rotate_speed_diff;
	}
	printf(GREEN "rotate speed changed to %f\n" RESET,
		cub->options.rotate_speed);
}

static void	handle_options(int keycode, t_cub *cub)
{
	// printf("key %d\n", keycode);
	if (keycode == KEY_O)
		print_key_options(cub);
	if (keycode == KEY_i)
		print_cub(cub);
	if (keycode == KEY_SP)
		print_options_status(&cub->options);
	if (keycode == KEY_F1)
	{
		cub->options.wall_col ^= 1;
		printf(YLLW"\n[changing wall collisions!]\n"RESET);
	}
	if (keycode == KEY_F2)
	{
		cub->options.show_minimap ^= 1;
		printf(YLLW"\n[showing/hiding minimap!]\n"RESET);
	}
	if (keycode == KEY_F3 || keycode == KEY_F4)
		change_move_speed(keycode, cub);
	if (keycode == KEY_F5 || keycode == KEY_F6)
		change_rotate_speed(keycode, cub);
}

int	key_release(int keycode, t_cub *cub)
{
	t_player	*player;

	// printf("key %d\n", keycode);
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
	else
		handle_options(keycode, cub);
	return (0);
}
