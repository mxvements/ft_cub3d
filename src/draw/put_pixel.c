#include "../includes/cub3d.h"

void	put_pixel(int col, int row, int color, t_cub *cub)
{
	int	index;

	if (col >= WIN_WIDTH || row >= WIN_HEIGHT || row < 0 || col < 0)
		return ;
	index = (row * cub->mlx->line_len) + (col * cub->mlx->bpp / 8);
	cub->mlx->img_addr[index] = color & 0xFF;
	cub->mlx->img_addr[index + 1] = (color >> 8) & 0xFF;
	cub->mlx->img_addr[index + 2] = (color >> 16) & 0xFF;
}

void	put_tile(t_cub *cub, void *tile_img, int row_offset, int col_offset)
{
	char	*tile_data;
	int		tile_bpp;
	int		util[2];
	int		map[2];
	int		color;

	tile_data = mlx_get_data_addr(tile_img, &tile_bpp, \
		&util[0], &util[1]);
	map[1] = 0;
	while (map[1] < MINIMAP_TILE)
	{
		map[0] = 0;
		while (map[0] < MINIMAP_TILE)
		{
			color = *(int *)(tile_data + (map[1] * util[0] \
				+ map[0] * (tile_bpp / 8)));
			if ((color & 0xFF000000) != 0xFF000000)
				put_pixel(map[0] + row_offset, map[1] + col_offset, color, cub);
			map[0]++;
		}
		map[1]++;
	}
}
