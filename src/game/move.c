
#include "../includes/cub3d.h"

static void	update_map(t_cub *cub, char player_char, float new_pos[2])
{
	t_player	*player;

	player = cub->map->player;
	if (cub->map->map[(int)round(new_pos[0])][(int)round(new_pos[1])] == ' ')
		return ;
	// printf();
	if ((int)round(new_pos[0]) >= (cub->map->rows - 0.5)
		|| (int)round(new_pos[0]) <= 0
		|| (int)round(new_pos[1]) >= (cub->map->cols - 0.5)
		|| (int)round(new_pos[1]) <= 0)
		return ;
	cub->map->map[(int)player->map_x][(int)player->map_y] = cub->map->old_position;
	cub->map->old_position = cub->map->map[(int)new_pos[0]][(int)new_pos[1]];
	cub->map->map[(int)new_pos[0]][(int)new_pos[1]] = player_char;
	// update player position
	player->map_x = (float)new_pos[0];
	player->map_y = (float)new_pos[1];
}

static void	rotate(t_player *player)
{
	float	angle_speed;

	angle_speed = PI / 32;
	if (player->move_keys.left_rotate)
		player->angle += angle_speed;
	if (player->move_keys.right_rotate)
		player->angle -= angle_speed;
	if (player->angle >= 2 * PI)
		player->angle -= 2 * PI;
	else if (player->angle < 0)
		player->angle += 2 * PI;
}

static void	move(t_cub *cub, float p[2], float move_x, float move_y)
{
	t_player	*player;
	float		speed;

	speed = 0.1;
	player = cub->map->player;
	p[0] += speed * move_x;
	p[1] += speed * move_y;
	update_map(cub, cub->map->map[(int)player->map_x][(int)player->map_y], p);
}

void	move_and_rotate(t_cub *cub)
{
	t_player	*player;
	float		new_pos[2];

	player = cub->map->player;
	new_pos[0] = player->map_x;
	new_pos[1] = player->map_y;
	rotate(player);
	if (player->move_keys.key_up)
		move(cub, new_pos, (float)cos(player->angle),
			(float)sin(player->angle));
	else if (player->move_keys.key_down)
		move(cub, new_pos, -(float)cos(player->angle),
			-(float)sin(player->angle));
	else if (player->move_keys.key_left)
		move(cub, new_pos, (float)cos(player->angle + PI / 2),
			(float)sin(player->angle + PI / 2));
	else if (player->move_keys.key_right)
		move(cub, new_pos, (float)cos(player->angle - PI / 2),
			(float)sin(player->angle - PI / 2));
}
