#include "../includes/cub3d.h"

/**
 * TODO: textures are not in 3d
 * TODO: unused function
 */
static void	put_texture(t_cub *cub, int col, int end)
{
	int	i;
	int	col_texture;

	i = 0;
	col_texture = col % 4;
	while (i < (PIXEL_SIZE - 1))
	{
		put_pixel(col, end, cub->textures->text[0][i], cub);
		i++;
	}
}

/* ----------------------------------------------------------------------- */

static void	put_line(t_cub *cub, int i)
{
	float	wall_height;
	int		start_row;
	int		end_row;

	if (cub->dist[i] > 0.1)
		wall_height = (WIN_HEIGHT * 16) / cub->dist[i];
	else
		wall_height = (WIN_HEIGHT * 16);
	start_row = ((WIN_HEIGHT - wall_height) / 2);
	end_row = (start_row + wall_height);
	/**
		* BUG: accesing out-of-bounds
		* end_row * PIXEL_SIZE + i >= PIXEL_SIZE * PIXEL_SIZE
		*
		* we need to map the texture to our wall_height
		* texture_y = (y - start_row) * (texture_height / wall height)
		* needs to be floats!
		*/
	while (end_row > start_row)
	{
		put_pixel(i, end_row, cub->textures->text[0][end_row * PIXEL_SIZE + i],
			cub);
		// put_texture(cub, i, end_row);
		end_row--;
	}
}

void	put_perspective(t_cub *cub)
{
	t_player	*player;
	float		fraction;
	float		start_angle;
	int			screen_col_idx;

	player = cub->map->player;
	fraction = (cub->options.fov * 2) / WIN_WIDTH;
	start_angle = player->angle - cub->options.fov;
	screen_col_idx = WIN_WIDTH;
	while (screen_col_idx > 0)
	{
		get_distance(cub, cos(start_angle), sin(start_angle), screen_col_idx);
		put_line(cub, screen_col_idx);
		start_angle += fraction;
		screen_col_idx--;
	}
}
