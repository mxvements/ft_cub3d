#include "../includes/cub3d.h"

int	is_touching_wall(float pcol, float prow, t_cub *cub)
{
	int	j;
	int	i;

	i = (prow - cub->minimap->start_x) / MINIMAP_TILE_SIZE;
	j = pcol / MINIMAP_TILE_SIZE;
	if (i < 0 || i >= cub->map->rows || j < 0 || j >= cub->map->cols)
		return (1); // Treat out-of-bounds as a wall
	if (cub->map->map[i][j] == '1')
		return (1);
	return (0);
}
/* ----------------------------------------------------------------------- */

static float	fix_fisheye(t_cub *cub, float delta_row, float delta_col,
		float d)
{
	float	angle;
	float	fixed_dist;

	// this distances has a fisheye effect
	angle = atan2(delta_col, delta_row) - cub->map->player->angle;
	// POSIBLE BUG on a atan2
	fixed_dist = fabs(d * cos(angle));
	// printf("dist: %f, fixed: %f\n", distance, fix_distance);
	return (fixed_dist);
}

static float	dist(t_cub *cub, float delta_row, float delta_col)
{
	float	dist;

	dist = sqrt(delta_row * delta_row + delta_col * delta_col);
	dist = fix_fisheye(cub, delta_row, delta_col, dist);
	return (dist);
}

static float	get_distance(t_cub *cub, float cos, float sin)
{
	const t_player	*pl = cub->map->player;
	float			ray_row;
	float			ray_col;
	float			d;

	ray_row = (float)pl->win_row;
	ray_col = (float)pl->win_col;
	while (!is_touching_wall(ray_col, ray_row, cub))
	{
		ray_row += cos;
		ray_col += sin;
	}
	d = dist(cub, (pl->win_row - ray_row), (pl->win_col - ray_col));
	return (d);
}
/* ----------------------------------------------------------------------- */

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

void	put_line(t_player *player, t_cub *cub, float angle, int i)
{
	float	wall_height;
	int		start_row;
	int		end_row;

	if (cub->dist[i] > 0.1)
		wall_height = (WIN_HEIGHT * 16) / cub->dist[i];
	//*(WIN_WIDTH / 2);//WALL_SIZE
	else
		wall_height = (WIN_HEIGHT * 16);
	//*(WIN_WIDTH / 2);//WALL_SIZE
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
		// hay que controlar que no dibuje encima del minimapa
		put_pixel(i, end_row, cub->textures->text[0][end_row * PIXEL_SIZE + i],
			cub);
		// put_texture(cub, i, end_row);
		end_row--;
	}
}

// this will only dray perpective
void	put_camera(t_cub *cub)
{
	t_player	*player;
	float		fraction;
	float		start_angle;
	int			screen_col_idx;
	int			color;

	player = cub->map->player;
	fraction = (cub->options.fov * 2) / WIN_WIDTH;
	start_angle = player->angle - cub->options.fov;
	screen_col_idx = WIN_WIDTH;
	while (screen_col_idx > 0)
	{
		cub->dist[screen_col_idx] = get_distance(cub, cos(start_angle),
				sin(start_angle));
		// dist is used inside put_line
		put_line(player, cub, start_angle, screen_col_idx);
		// previous color: 255
		start_angle += fraction;
		screen_col_idx--;
	}
}
