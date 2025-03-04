#include "../includes/cub3d.h"

void	minimap_put_player(t_cub *cub, int color)
{
	t_player	*player;
	float start_row;
	float start_col;

	player = cub->map->player;
	start_row = ((player->map_row * MINIMAP_PX) + \
		cub->minimap->start_x + MINIMAP_PX / 4);
	start_col = ((player->map_col * MINIMAP_PX) + MINIMAP_PX / 4);
	//to keep it centered with a minimap of size MINIMAP_RADIUS:
	// start_row = (player->win_row - (player->map_row * MINIMAP_PX) )+ (MINIMAP_RADIUS / 2);
	// start_col = (player->win_col - (player->map_col * MINIMAP_PX) )+ (MINIMAP_RADIUS / 2);
	put_square(start_col, start_row, color, cub);
}

void	minimap_put_fov(t_cub *cub, int color_fov)
{
	float	fraction;
	float	start_angle;
	int		screen_col_idx;
	float	ray_row;
	float	ray_col;

	fraction = (cub->options.fov) / WIN_WIDTH;
	start_angle = cub->map->player->angle - (cub->options.fov / 2);
	screen_col_idx = WIN_WIDTH;
	while (screen_col_idx > 0)
	{
		ray_row = (float)cub->map->player->win_row; //do the same as above
		ray_col = (float)cub->map->player->win_col; //do the same as above
		while (!is_touching_wall(ray_col, ray_row, cub)
			&& cub->options.show_minimap == 1)
		{
			put_pixel((int)ray_col, (int)ray_row, color_fov, cub);
			ray_row += cos(start_angle);
			ray_col += sin(start_angle);
		}
		start_angle += fraction;
		screen_col_idx--;
	}
}

void	minimap_put_axis(t_cub *cub, int color_axis)
{
	t_player	*player;
	float		ray_row;
	float		ray_col;
	float		cos_angle;
	float		sin_angle;

	player = cub->map->player;
	ray_row = cub->map->player->win_row; //do the same as above
	ray_col = cub->map->player->win_col; //do the same as above
	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	while (!is_touching_wall(ray_col, ray_row, cub)
		&& cub->options.show_minimap == 1)
	{
		put_pixel((int)ray_col, (int)ray_row, color_axis, cub);
		ray_row += cos_angle;
		ray_col += sin_angle;
	}
}
