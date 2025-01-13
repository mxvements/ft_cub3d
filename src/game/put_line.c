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

void	put_line(t_player *player, t_cub *cub, float angle, int i, int color)
{
	float	cos_angle;
	float	sin_angle;
	float	ray_row;
	float	ray_col;
	// float	dist;
	// float	wall_height;
	// int		start_y;
	// int		end;

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
	// //perspective
	// dist = distance(ray_x, player->x, ray_y, player->y, game);
	// wall_height = (TILE_SIZE / dist) * (WIN_WIDTH / 2);
	// start_y = (WIN_HEIGHT - wall_height) / 2;
	// end = start_y + wall_height;
	// while (start_y < end)
	// {
	// 	if (DEBUG == 1)
	// 		put_pixel(i, start_y, 255, game);
	// 	start_y++;
	// }
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
	while (i < (cub->map->cols * MINIMAP_TILE_SIZE))
	{
		put_line(player, cub, start_angle, i, 0xAA6666);
		start_angle += fraction;
		i++;
	}
}
