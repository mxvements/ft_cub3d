#include "../includes/cub3d.h"

static void	texture_ceiling(t_cub *cub, int start_row, int i)
{
	int	k;

	k = 0;
	while (k < start_row)
	{
		put_pixel(i, k, cub->textures->ceiling, cub);
		k++;
	}
}

static void	texture_floor(t_cub *cub, int end_row, int i)
{
	int	k;

	k = end_row;
	while (k < WIN_WIDTH)
	{
		put_pixel(i, k, cub->textures->floor, cub);
		k++;
	}
}

static float	wall_offset(t_cub *cub, int i)
{
	const int	collistion_dir = cub->hits[i].collision_dir;

	if (collistion_dir == VERTICAL)
		return (fmod(cub->hits[i].ray[1], MINIMAP_TILE));
	else
		return (fmod(cub->hits[i].ray[0], MINIMAP_TILE));
}

static void	texture_wall(t_cub *cub, int start_row, int end_row,
		float wall_height, int i)
{
	const int	wall_side = cub->hits[i].texture_idx;
	int			j;
	int			texture_x;
	int			texture_y;
	int			color;

	printf("Collision dir: %d | Side: %d | Offset: %f\n",
		cub->hits[i].collision_dir, cub->hits[i].texture_idx, wall_offset(cub,
			i));
	texture_x = (int)((wall_offset(cub, i) / MINIMAP_TILE) * PIXEL_SIZE);
	// no debe de la pantalla sino de la casilla
	j = start_row;
	while (end_row > j)
	{
		texture_y = (j - start_row) * (PIXEL_SIZE / wall_height);
		color = cub->textures->text[wall_side][texture_y * PIXEL_SIZE
			+ texture_x];
		put_pixel(i, j, color, cub);
		j++;
	}
}

static void	put_line(t_cub *cub, int i)
{
	float	wall_height;
	int		start_row;
	int		end_row;

	// const float  dist = cub->hits[i].dist;
	// int		color;
	// int		texture_x;
	// int		texture_y;
	//
	if (cub->hits[i].dist > 0.1)
		wall_height = (WIN_HEIGHT * 16) / cub->hits[i].dist;
	else
		wall_height = (WIN_HEIGHT * 16);
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
