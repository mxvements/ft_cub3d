#include "../includes/cub3d.h"

static void	texture_wall(t_cub *cub, int row[2], float wall_height, int i)
{
	const int	side = cub->hits[i].texture_idx;
	int			j;
	float		tex_x;
	float		tex_y;
	int			color;

	/**
	 * offset/MINIMAP_TILE gives a float between [0,1] to know 
	 * at which point in the minimap tile the ray has hit 
	 */
	float offset = (wall_offset(cub, i) / MINIMAP_TILE);
	tex_x = (int)round((wall_offset(cub, i) /MINIMAP_TILE) * PIXEL_SIZE);
	// printf("offset: %f - texture_x: %f\n", offset, texture_x);
	j = row[0];
	while (row[1] > j)
	{
		tex_y = (int)round((j - row[0]) * (PIXEL_SIZE / wall_height));
		color = cub->textures->text[side][(int)round(tex_y \
			* PIXEL_SIZE + tex_x)];
		put_pixel(i, j, color, cub);
		j++;
	}
}

static void	put_line(t_cub *cub, int i)
{
	float	wall_height;
	int		row[2];
	// printf("-->%f\n", cub->hits[i].dist);
	if (cub->hits[i].dist < 0.01f)
		wall_height = (WIN_HEIGHT * MINIMAP_TILE);
	else
		wall_height = (WIN_HEIGHT * MINIMAP_TILE) / cub->hits[i].dist;
	row[0] = ((WIN_HEIGHT - wall_height) / 2);
	row[1] = (row[0] + wall_height);
	texture_ceiling(cub, row[0], i);
	texture_wall(cub, row, wall_height, i);
	texture_floor(cub, row[1], i);
}

void	put_perspective(t_cub *cub)
{
	t_player	*player;
	float		fraction;
	float		start_angle;
	int			screen_col_idx;

	player = cub->map->player;
	fraction = (cub->options.fov) / WIN_WIDTH;
	start_angle = player->angle - (cub->options.fov / 2);
	screen_col_idx = WIN_WIDTH;
	while (screen_col_idx > 0)
	{
		get_distance(cub, cos(start_angle), sin(start_angle), screen_col_idx);
		put_line(cub, screen_col_idx);
		start_angle += fraction;
		screen_col_idx--;
	}
}
