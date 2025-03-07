/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciama2 <luciama2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:04:52 by luciama2          #+#    #+#             */
/*   Updated: 2025/03/07 20:04:53 by luciama2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	key_press(int keycode, t_cub *cub)
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
		win_close(cub);
	return (0);
}
