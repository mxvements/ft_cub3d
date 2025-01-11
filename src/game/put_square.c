#include "../includes/cub3d.h"

void	put_square(int row, int col, int size, int color, t_cub *cub)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
			put_pixel(row + i, col + j, color, cub);
	}
}
