#include "../includes/cub3d.h"

static void	texture_ceiling(t_cub *cub, int start_row, int i)
{
	int	k;

	k = 0;
	while (k <= start_row)
	{
		put_pixel(i, k, cub->textures->ceiling, cub);
		k++;
	}
}

static void	texture_floor(t_cub *cub, int end_row, int i)
{
	int	k;

	k = end_row;
	while (k <= WIN_WIDTH)
	{
		put_pixel(i, k, cub->textures->floor, cub);
		k++;
	}
}

static float	wall_offset(t_cub *cub, int i)
{
	const float world_row = (cub->hits[i].ray[0] - cub->minimap->start_x);
	const float world_col = cub->hits[i].ray[1];
	const int	collistion_dir = cub->hits[i].collision_dir;
	float		offset;

	if (collistion_dir == VERTICAL)
		offset = fmod(world_col, MINIMAP_TILE);
	else
		offset = fmod(world_row, MINIMAP_TILE);
	return (offset);
}

//bounds[2] o range[2]
//start_row -> bound[0]
//end_row -> bound[1]
static void	texture_wall(t_cub *cub, int start_row, int end_row,
		float wall_height, int i)
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
	j = start_row;
	while (end_row > j)
	{
		tex_y = (int)round((j - start_row) * (PIXEL_SIZE / wall_height));
		color = cub->textures->text[side][(int)round(tex_y * PIXEL_SIZE + tex_x)];
		put_pixel(i, j, color, cub);
		j++;
	}
}

static void	put_line(t_cub *cub, int i)
{
	float	wall_height;
	int		start_row;
	int		end_row;

	if (cub->hits[i].dist > 0.1)
		wall_height = (WIN_HEIGHT * MINIMAP_TILE) / cub->hits[i].dist;
	else
		wall_height = (WIN_HEIGHT * MINIMAP_TILE);
	start_row = ((WIN_HEIGHT - wall_height) / 2);
	end_row = (start_row + wall_height);
	texture_ceiling(cub, start_row, i);
	texture_wall(cub, start_row, end_row, wall_height, i);
	texture_floor(cub, end_row, i);
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
