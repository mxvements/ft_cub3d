#include "../includes/cub3d.h"

int	touch_wall(float pcol, float prow, t_cub *cub)
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
static float    distance(float row2, float row1, float col2, float col1, t_cub *cub)
{
    float   delta_row;
    float   delta_col;
    float   distance;
    delta_row = (row1 - row2);
    delta_col = (col1 - col2);
    distance = sqrt(delta_row * delta_row + delta_col * delta_col);
    // printf("Player Position: (%f, %f), Ray Hit: (%f, %f), Distance: %f\n", row1, col1, row2, col2, distance);
    //this distances has a fisheye effect this fix
    float angle = atan2(delta_col, delta_row)- cub->map->player->angle; //POSIBLE BUG
    float fix_distance = fabs(distance * cos(angle));
    // printf("dist: %f, fixed: %f\n", distance, fix_distance);
    return (fix_distance);
}


static float whileTouch(t_player *player, t_cub *cub, float cos_angle, float sin_angle, int color)
{
    t_image image;
    float   ray_row;
    float   ray_col;
    image.img = NULL;
    const float player_row = player->map_row * MINIMAP_TILE_SIZE + cub->minimap->start_x
        + MINIMAP_TILE_SIZE / 2;
    const float player_col  = player->map_col * MINIMAP_TILE_SIZE + MINIMAP_TILE_SIZE / 2;
    ray_row = (float)player_row;
    ray_col = (float)player_col;
    // FOV on minimap
    while (!touch_wall(ray_col, ray_row, cub))
    {
		if (cub->options.show_minimap == 1)
        	put_pixel((int)ray_col, (int)ray_row, color, cub);
        ray_row += cos_angle;
        ray_col += sin_angle;
    }
    //perspective
    return distance(ray_row, player_row, ray_col, player_col, cub);
}

/* static void	put_texture(t_cub *cub, int col, int end)
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
} */

/* ----------------------------------------------------------------------- */

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

static void	texture_wall(t_cub *cub, int start_row, int end_row,float wall_height, int i)
{
	int	j;
	int texture_x;
	int texture_y;
	int color;

	texture_x = i % PIXEL_SIZE;
    j = start_row;
    while (end_row > j)
    {
        texture_y = (j - start_row) * (PIXEL_SIZE / wall_height);
        color = cub->textures->text[0][texture_y * PIXEL_SIZE + texture_x];
        put_pixel(i, j, color, cub);
		j++;
	}
}

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
	texture_ceiling(cub, start_row, i);
	texture_wall(cub, start_row, end_row,wall_height, i);
	texture_floor(cub, end_row, i);
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
