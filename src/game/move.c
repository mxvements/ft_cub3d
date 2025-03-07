/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciama2 <luciama2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:04:44 by luciama2          #+#    #+#             */
/*   Updated: 2025/03/07 20:04:45 by luciama2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	update_map(t_cub *cub, float new_pos[2])
{
	t_player	*player;
	int			new_map_pos[2];

	player = cub->map->player;
	new_map_pos[0] = (int)(new_pos[0]);
	new_map_pos[1] = (int)(new_pos[1]);
	if(cub->map->map[new_map_pos[0]][new_map_pos[1]])
	if(new_pos[0] < 0 || new_pos[0] >= cub->map->rows-1 || new_pos[1] < 0 || new_pos[1] >= cub->map->cols-1 )
		return;
	player->map_row = (float)new_pos[0];
	player->map_col = (float)new_pos[1];
}

static void	rotate(t_cub *cub)
{
	t_player	*player;
	float		angle_speed;

	player = cub->map->player;
	angle_speed = cub->options.rotate_speed;
	if (player->move_keys.left_rotate)
		player->angle += angle_speed;
	if (player->move_keys.right_rotate)
		player->angle -= angle_speed;
	if (player->angle >= 2 * PI)
		player->angle -= 2 * PI;
	else if (player->angle < 0)
		player->angle += 2 * PI;
}

static void	move_and_update_map(t_cub *cub, float pos[2], float move_x,
		float move_y)
{
	t_player	*player;
	float		speed;
	char		limit_char;

	speed = cub->options.move_speed;
	player = cub->map->player;

	pos[0] += speed * move_x;
	pos[1] += speed * move_y;
	if (cub->options.wall_col == 0)
		limit_char = ' ';
	else
		limit_char = '1';
	if (cub->map->map[(int)round(pos[0])][(int)round(pos[1])] == limit_char)
		return ;
	update_map(cub, pos);
}

void	move_and_rotate(t_cub *cub)
{
	t_player	*player;
	float		new_pos[2];

	player = cub->map->player;
	new_pos[0] = player->map_row;
	new_pos[1] = player->map_col;
	rotate(cub);
	if (player->move_keys.key_up)
		move_and_update_map(cub, new_pos, (float)cos(player->angle),
			(float)sin(player->angle));
	else if (player->move_keys.key_down)
		move_and_update_map(cub, new_pos, -(float)cos(player->angle),
			-(float)sin(player->angle));
	else if (player->move_keys.key_left)
		move_and_update_map(cub, new_pos, (float)cos(player->angle + PI / 2),
			(float)sin(player->angle + PI / 2));
	else if (player->move_keys.key_right)
		move_and_update_map(cub, new_pos, (float)cos(player->angle - PI / 2),
			(float)sin(player->angle - PI / 2));
}
