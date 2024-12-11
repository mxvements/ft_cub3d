#include "../includes/cub3d.h"

void print_map(t_map *map)
{
	printf("\tmap struct\n");
	if (map->cols != 0 && map->rows != 0)
		printf("\tmap (rows, cols): (%d, %d)\n", map->rows, map->cols);
	if (map->map)
	{
		printf("\tmap:\n");
		strarr_print(map->map);
	}
}

void print_texture(t_texture *tx)
{
	int	i;

	printf("\ttexture struct:\n");
	printf("\twall side texturs:\n");
	i = -1;
	while (++i < WALL_SIDES && tx->wall[i] != 0)
		printf("\t%s", tx->wall[i]);
	if (tx->floor != 0)
		printf("\tfloor color: %lli", tx->floor);
	if (tx->ceiling != 0)
		printf("\tceiling color: %lli", tx->ceiling);
}

void print_player(t_player *pl)
{
	printf("\tplayer struct:\n");
	if (pl->x != 0 && pl->y != 0)
		printf("\tplayer position (x, y): (%f, %f)\n", pl->x, pl->y);
	if (pl->dirX != 0 && pl->dirY != 0)
		printf("\tplayer direction (x, y): (%f, %f)\n", pl->dirX, pl->dirY);
	if (pl->walk != 0)
		printf("\twalk direction (-1 or 0 or 1): (%d)\n", pl->walk);
	if (pl->spin != 0)
		printf("\tspin dir (1=cw, -1=ccw): (%d)\n", pl->spin);
}

void	print_cub(t_cub *cub)
{
	printf("cub status:\n");
	if (cub->fd)
		printf("\tfd:%d\n", cub->fd);
	if (cub->map)
		print_map(cub->map);
	if (cub->textures)
		print_texture(cub->textures);
	if (cub->player)
		print_player(cub->player);
}
