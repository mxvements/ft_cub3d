
#include "../includes/cub3d.h"

void update_map(t_cub *cub, char player_char, float new_pos[2])
{
	t_player	*player;
	player = cub->map->player;
	
	//cambiar el espacio por muro en bonus, poner variable
	if (cub->map->map[(int)new_pos[0]][(int)new_pos[1]] == ' ')
		return ;
	//update map with new positions
	cub->map->map[(int)player->x][(int)player->y] = cub->map->old_position;
	cub->map->old_position = cub->map->map[(int)new_pos[0]][(int)new_pos[1]];
	cub->map->map[(int)new_pos[0]][(int)new_pos[1]] = player_char;
	// update player position
	player->x = (int)new_pos[0];
	player->y = (int)new_pos[1];

}

void	move(t_cub *cub)
{
	char		**map;
	t_player	*player;
	char		player_char;
	float			speed;
	float		angle_speed;
	float new_pos[2];

	// printf(ORANGE "Se esta moviendo.\n" RESET);
	player = cub->map->player;
	new_pos[0] = player->x;
	new_pos[1] = player->y;
	// print_player(player);
	map = cub->map->map;
	speed = 1;
	angle_speed = PI / 16;
	player_char = cub->map->map[(int)player->x][(int)player->y];

	// move
	if (player->move_keys.left_rotate)
		player->angle -= angle_speed;
	if (player->move_keys.right_rotate)
		player->angle += angle_speed;
	if (player->angle > 2 * PI)
		player->angle = 0;
	if (player->angle > 2 * PI)
		player->angle = 2 * PI;
	if (player->move_keys.key_up)
	{
		new_pos[0] -= speed * (float)cos(player->angle);
		new_pos[1] -= speed * (float)sin(player->angle);
		update_map(cub, player_char, new_pos);
	}
	if (player->move_keys.key_down)
	{
		new_pos[0] += speed * (float)cos(player->angle);
		new_pos[1] += speed * (float)sin(player->angle);
		update_map(cub, player_char, new_pos);

	}
	if (player->move_keys.key_left)
	{
		new_pos[0] -= speed * (float)cos(player->angle + PI / 2);
		new_pos[1] -= speed * (float)sin(player->angle + PI / 2);
		update_map(cub, player_char, new_pos);

	}
	if (player->move_keys.key_right)
	{
		new_pos[0] += speed * (float)cos(player->angle + PI / 2);
		new_pos[1] += speed * (float)sin(player->angle + PI / 2);
		printf("new pos: (%f, %f)\n", new_pos[0], new_pos[1]);
		update_map(cub, player_char, new_pos);

	}
}
