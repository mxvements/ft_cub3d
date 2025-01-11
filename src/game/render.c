
#include "../includes/cub3d.h"
/*
void	put_pixel(int x, int y, int color, t_cub *cub)
{
	t_mlx	*mlx;
	int		index;

	mlx = cub->mlx;
	if (x >= WIN_WIDTH || y >= WIN_HEIGHT || x < 0 || y < 0)
		return ;
	index = (y * mlx->line_len) + (x * mlx->bpp / 8);
	mlx->img_addr[index] = color & 0XFF;                    // blue channel
	mlx->img_addr[index + 1] = (color >> 8) & 0xFF;  // green channel
	mlx->img_addr[index + 2] = (color >> 16) & 0xFF; // red channel
}

// MINIMAP DRAW AXIS OF CAMERA

// raycasting on the minimap
int	touch_wall(float px, float py, t_cub *cub)
{
	int	j;
	int	i;

	j = py;
	i = px;
	if (cub->map->map[i][j] == '1')
		return (1);
	return (0);
}

static void	minimap_axis(t_cub *cub, int color)
{
	t_player	*player;
	float		ray_x;
	float		ray_y;
	float		cos_angle;
	float		sin_angle;
		const float start_ray_x = cub->minimap->start_x;

	(void)color;
	player = cub->map->player;
	print_player(player); // TO DEBUG
	ray_x = player->map_x;
	ray_y = player->map_y;
	printf(ROSE "ray_x, ray_y: (%f, %f)\n" RESET, ray_x, ray_y);
	cos_angle = player->dirX; // cos(player->angle);
	sin_angle = player->dirY; // sin(player->angle);
	while (!touch_wall(ray_x, ray_y, cub))
	{
		printf(ROSE "start row of minimap:  %f\n" RESET, start_ray_x);
		printf(ROSE "ray_x, ray_y: (%f, %f)\n" RESET, ray_x, ray_y);
		// int pos[2] = {ray_x, ray_y};
		// int vector[2] =  {cos_angle, sin_angle};
		// put_pixel(ray_x, ray_y, color, cub);
		// ray_x and ray_y need to take into account the position of the minimap
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
	mlx_put_image_to_window(cub->mlx->mlx_ptr, cub->mlx->win,
		cub->mlx->img, 0, 0);
} */

/* ------------------------------------------------------------------------- */

void	render(t_cub *cub, t_map *map)
{
	(void)map;
	// mlx_clear_window(cub->mlx->mlx_ptr, cub->mlx->win);
	minimap_render(cub);
	// minimap_axis(cub, 0xFF0000);
}
