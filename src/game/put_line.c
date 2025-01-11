#include "../includes/cub3d.h"

int	touch_wall(float pcol, float prow, t_cub *cub)
{
	int	j;
	int	i;

	printf("in touch wall, prow,pcol (%f, %f)\n", prow, pcol);

	i = (prow - cub->minimap->start_x) / MINIMAP_TILE_SIZE ;
	j = pcol / MINIMAP_TILE_SIZE;
	printf("in touch wall, j i (%d, %d)\n", i, j);
	if (cub->map->map[i][j] == '1')
		return (1);
	return (0);
}

// void	put_line(t_player *player, t_cub *game, float start_x, int i,
// 		int color)
// {
// 	float	cos_angle;
// 	float	sin_angle;
// 	float	ray_x;
// 	float	ray_y;
// 	float	dist;
// 	float	wall_height;
// 	int		start_y;
// 	int		end;
// 	cos_angle = cos(start_x);
// 	sin_angle = sin(start_x);
// 	ray_x = player->x; //+ PLAYER_SIZE / 2;
// 	ray_y = player->y; //+ PLAYER_SIZE / 2;
// 	//FOV on minimap
// 	while (!touch_wall(ray_x, ray_y, game))
// 	{
// 		if (DEBUG != 1)
// 			put_pixel(ray_x, ray_y, color, game);
// 		ray_x += cos_angle;
// 		ray_y += sin_angle;
// 	}
// 	//perspective
// 	dist = distance(ray_x, player->x, ray_y, player->y, game);
// 	wall_height = (TILE_SIZE / dist) * (WIN_WIDTH / 2);
// 	start_y = (WIN_HEIGHT - wall_height) / 2;
// 	end = start_y + wall_height;
// 	while (start_y < end)
// 	{
// 		if (DEBUG == 1)
// 			put_pixel(i, start_y, 255, game);
// 		start_y++;
// 	}
// }

// void	put_axis(t_cub *cub, int color)
// {
// 	t_player	*player;
// 	float		ray_x;
// 	float		ray_y;
// 	float		cos_angle;
// 	float		sin_angle;
// 	player = cub->map->player;
// 	ray_x = player->x  ;// + MINIMAP_TILE_SIZE / 2;
// 	ray_y = player->y;// + MINIMAP_TILE_SIZE / 2;
// 	printf("ray: (%f, %f\n)", ray_x, ray_y);
// 	printf("angle: %f\n", cub->map->player->angle);
// 	cos_angle = cos(player->angle);
// 	sin_angle = sin(player->angle);
// 	while (!touch_wall(ray_x, ray_y, cub))
// 	{
// 		// if (DEBUG != 1)
// 		float to_print_x = ((ray_x )) + MINIMAP_TILE_SIZE / 2;
// 		float to_print_y = (ray_y * MINIMAP_TILE_SIZE) + MINIMAP_TILE_SIZE / 2;
// 		// printf("to print : (%f, %f)\n", to_print_x, to_print_y);
// 		put_pixel(to_print_y, to_print_x, color, cub);
// 		ray_x += cos_angle;
// 		ray_y += sin_angle;
// 	}
// 	mlx_put_image_to_window(cub->mlx->mlx_ptr, cub->mlx->win, cub->mlx->img,0, cub->minimap->start_x);
// }

void put_axis(t_cub *cub, int color)
{
    t_player *player;
    float ray_row, ray_col, cos_angle, sin_angle;

    player = cub->map->player;
    ray_row = player->x * MINIMAP_TILE_SIZE + cub->minimap->start_x +  MINIMAP_TILE_SIZE / 2;
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


