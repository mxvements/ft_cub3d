#include "../includes/cub3d.h"

static void	put_square(int start[2], int size, int color, t_cub *cub)
{
	int	row;
	int	col;

	row = -1;
	while (++row < size)
	{
		col = -1;
		while (++col < size)
			put_pixel(start[0] + row, start[1] + col, color, cub);
	}
}

void	minimap_put_player(t_cub *cub, int color)
{
	t_player	*player;
	float		start[2];

	player = cub->map->player;
	start[0] = (int)((player->map_row * MINIMAP_TILE) + \
		cub->minimap->start_x + MINIMAP_TILE / 4);
	start[1] = (int)((player->map_col * MINIMAP_TILE) + MINIMAP_TILE / 4);
	put_square(start, MINIMAP_TILE / 2, color, cub);
}
