#include "../includes/cub3d.h"

static void	put_square(int prow, int pcol, int color, t_cub *cub)
{
	int	row;
	int	col;
	int	size = MINIMAP_PX / 2;

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
	t_player	*player;
	float start_row;
	float start_col;

	player = cub->map->player;
	start_row = ((player->map_row * MINIMAP_PX) + \
		cub->minimap->start_x + MINIMAP_PX / 4);
	start_col = ((player->map_col * MINIMAP_PX) + MINIMAP_PX / 4);
	put_square(start_col, start_row, color, cub);
}
