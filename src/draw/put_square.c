#include "../includes/cub3d.h"

void	put_square(int prow, int pcol, int size, int color, t_cub *cub)
{
	int row;
	int col;

	row = -1;
	while (++row < size)
	{
		col = -1;
		while (++col < size)
			put_pixel(prow + row, pcol + col, color, cub);
	}
}

void	minimap_put_player(t_cub *cub, int color)
{
	t_player *player;
	float start_row;
	float start_col;

	player = cub->map->player;
	// printf("player_x, player_y (%f, %f)\n", player->map_row, player->map_col);
	start_row = (player->map_row * MINIMAP_TILE) + cub->minimap->start_x + MINIMAP_TILE/4;
	start_col = (player->map_col * MINIMAP_TILE) + MINIMAP_TILE/4;
	// printf(RED"start_row, start_col (%f, %f)\n"RESET, start_row, start_col);
	put_square(start_col, start_row, MINIMAP_TILE/2, color, cub);
}
