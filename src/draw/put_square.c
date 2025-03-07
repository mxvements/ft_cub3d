#include "../includes/cub3d.h"

void	put_square(int prow, int pcol, int color, t_cub *cub)
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


