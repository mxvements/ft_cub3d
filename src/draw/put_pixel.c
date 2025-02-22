#include "../includes/cub3d.h"

void	put_pixel(int col, int row, int color, t_cub *cub)
{
	int	index;

	if (col >= WIN_WIDTH || row >= WIN_HEIGHT || row < 0 || col < 0)
		return ;
	index = (row * cub->mlx->line_len) + (col * cub->mlx->bpp / 8);
	cub->mlx->img_addr[index] = color & 0xFF;             // blue channel
	cub->mlx->img_addr[index + 1] = (color >> 8) & 0xFF;  // green channel
	cub->mlx->img_addr[index + 2] = (color >> 16) & 0xFF; // red channel
}

void put_tile(t_cub *cub, void *tile_img, int row_offset, int col_offset)
{
    char *tile_data;
    int tile_bpp, tile_line_len, tile_endian;
    int row, col;

    tile_data = mlx_get_data_addr(tile_img, &tile_bpp, &tile_line_len, &tile_endian);

    for (col = 0; col < MINIMAP_TILE; col++)
    {
        for (row = 0; row < MINIMAP_TILE; row++)
        {
            int color = *(int *)(tile_data + (col * tile_line_len + row * (tile_bpp / 8)));
            if ((color & 0xFF000000) != 0xFF000000) // Skip transparent pixels
                put_pixel(row + row_offset, col + col_offset, color, cub);
        }
    }
}
