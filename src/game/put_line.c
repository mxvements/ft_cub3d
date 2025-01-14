#include "../includes/cub3d.h"

int	touch_wall(float pcol, float prow, t_cub *cub)
{
	int	j;
	int	i;

	// printf("in touch wall, prow,pcol (%f, %f)\n", prow, pcol);
	i = (prow - cub->minimap->start_x) / MINIMAP_TILE_SIZE;
	j = pcol / MINIMAP_TILE_SIZE;
	// printf("in touch wall, j i (%d, %d)\n", i, j);

	if (i < 0 || i >= cub->map->rows || j < 0 || j >= cub->map->cols)
        return (1); // Treat out-of-bounds as a wall

	if (cub->map->map[i][j] == '1')
		return (1);
	return (0);
}
static float	distance(float row2, float row1, float col2, float col1, t_cub *cub)
{
	float	delta_row;
	float	delta_col;
	float	distance;

	delta_row = row2 - row1;
	delta_col = col2 - col1;
	distance = sqrt(delta_row * delta_row + delta_col * delta_col);
	//this distances has a fisheye effect this fix
	float angle = atan2(delta_col, delta_row)- cub->map->player->angle; //POSIBLE BUG
	float fix_distance = distance * cos(angle);
	return (fix_distance);
}
void	put_line(t_player *player, t_cub *cub, float angle, int i, int color)
{
	float	cos_angle;
	float	sin_angle;
	float	ray_row;
	float	ray_col;

	float	dist;
	float	wall_height;
	int		start_row;
	int		end;

	cos_angle = cos(angle);
	sin_angle = sin(angle);
	ray_row = player->x * MINIMAP_TILE_SIZE + cub->minimap->start_x
		+ MINIMAP_TILE_SIZE / 2;
	ray_col = player->y * MINIMAP_TILE_SIZE + MINIMAP_TILE_SIZE / 2;
	// FOV on minimap
	while (!touch_wall(ray_col, ray_row, cub))
	{
		
		put_pixel((int)ray_col, (int)ray_row, color, cub);
		ray_row += cos_angle;
		ray_col += sin_angle;
	}
	//perspective
	dist = distance(ray_row, player->x, ray_col, player->y, cub);
	wall_height = (32 / dist) * (WIN_WIDTH / 2);
	start_row = (WIN_HEIGHT - wall_height) / 2;
	end = start_row + wall_height;
	while (start_row < end)
	{
		//hay que controlar que no dibuje encima del minimapa
		put_pixel(i, start_row, 255, cub);
		start_row++;
	}
}

void	minimap_put_axis(t_cub *cub, int color)
{
	t_player	*player;
	float		ray_row;
	float		ray_col;
	float		cos_angle;
	float		sin_angle;

	player = cub->map->player;
	ray_row = player->x * MINIMAP_TILE_SIZE + cub->minimap->start_x
		+ MINIMAP_TILE_SIZE / 2;
	ray_col = player->y * MINIMAP_TILE_SIZE + MINIMAP_TILE_SIZE / 2;
	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	while (!touch_wall(ray_col, ray_row, cub))
	{

		put_pixel((int)ray_col, (int)ray_row, color, cub);
		ray_row += cos_angle;
		ray_col += sin_angle;
	}
}
void	put_camera(t_cub *cub)
{
	t_player	*player;
	const float	FOV = PI / 6;
	float		fraction;
	float		start_angle;
	int			i;

	player = cub->map->player;
	fraction = (FOV * 2) / (cub->map->cols * MINIMAP_TILE_SIZE);
	start_angle = player->angle - FOV;
	i = 0;
	while (i < WIN_WIDTH) //i < (cub->map->cols * MINIMAP_TILE_SIZE)
	{
		put_line(player, cub, start_angle, i, 0xAA6666);
		start_angle += fraction;
		i++;
	}
}
