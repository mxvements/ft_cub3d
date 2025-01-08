
#include "../includes/cub3d.h"

void	move(t_cub *cub)
{
	char		**map;
	t_player	*player;
	char		player_char;
	int			player_posX;
	int			player_posY;
	
	printf(ORANGE "Se esta moviendo.\n" RESET);

	player = cub->map->player;
	print_player(player);
	map = cub->map->map;
	player_posX = player->x;
	player_posY = player->y;
	player_char = cub->map->map[player_posX][player_posY];
	//update player cell to floor
	cub->map->map[player_posX][player_posY] = '0';
	//update move cell to player
	cub->map->map[player_posX + player->walk[0]][player_posY + player->walk[1]] = player_char;
	//update player position
	player->x = player_posX + player->walk[0];
	player->y = player_posY + player->walk[1];
}

