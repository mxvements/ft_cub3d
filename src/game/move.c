
#include "../includes/cub3d.h"


void	update_map(t_cub *cub, char player_char, float new_pos[2])
{
	t_player	*player;

	player = cub->map->player;
	// cambiar el espacio por muro en bonus, poner variable
	if (cub->map->map[(int)new_pos[0]][(int)new_pos[1]] == ' ')
		return ;
	// update map with new positions
	cub->map->map[(int)player->x][(int)player->y] = cub->map->old_position;
	cub->map->old_position = cub->map->map[(int)new_pos[0]][(int)new_pos[1]];
	cub->map->map[(int)new_pos[0]][(int)new_pos[1]] = player_char;
	// update player position
	player->x = (float)new_pos[0];
	player->y = (float)new_pos[1];
}

void	move(t_cub *cub)
{
	t_player	*player;
	float		speed;
	float		angle_speed;
	float		new_pos[2];

	speed = 0.5;
	angle_speed = PI / 16;
	player = cub->map->player;
	new_pos[0] = player->x;
	new_pos[1] = player->y;
	// rotate
	if (player->move_keys.left_rotate)
		player->angle -= angle_speed;
	if (player->move_keys.right_rotate)
		player->angle += angle_speed;
	if (player->angle >= 2 * PI)
		player->angle -= 2 * PI;
	else if (player->angle < 0)
		player->angle += 2 * PI;

	// move
	if (player->move_keys.key_up)
	{
		new_pos[0] += speed * (float)cos(player->angle);
		new_pos[1] += speed * (float)sin(player->angle);
		update_map(cub, cub->map->map[(int)player->x][(int)player->y], new_pos);
	}
	else if (player->move_keys.key_down)
	{
		new_pos[0] -= speed * (float)cos(player->angle);
		new_pos[1] -= speed * (float)sin(player->angle);
		update_map(cub, cub->map->map[(int)player->x][(int)player->y], new_pos);
	}
	else if (player->move_keys.key_left)
	{
		new_pos[0] += speed * (float)cos(player->angle + PI / 2);
		new_pos[1] += speed * (float)sin(player->angle + PI / 2);
		update_map(cub, cub->map->map[(int)player->x][(int)player->y], new_pos);
	}
	else if (player->move_keys.key_right)
	{
		new_pos[0] += speed * (float)cos(player->angle - PI / 2);
		new_pos[1] += speed * (float)sin(player->angle - PI / 2);
		update_map(cub, cub->map->map[(int)player->x][(int)player->y], new_pos);
	}
}
