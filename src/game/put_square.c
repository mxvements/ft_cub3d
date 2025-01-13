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
			put_pixel( prow + row, pcol + col, color, cub);
	}
}

void	minimap_put_player(t_cub *cub, int color)
{
	t_player *player;
	float start_row;
	float start_col;

	player = cub->map->map;
	start_row = player->x * MINIMAP_TILE_SIZE + cub->minimap->start_x;
	start_col = player->y * MINIMAP_TILE_SIZE;
	put_square(start_col, start_row, MINIMAP_TILE_SIZE, color, cub);
}