#include "../includes/cub3d.h"


void print_player(t_player *pl)
{
	printf(YLLW"[player struct]\n"RESET);
	if (pl->x != 0 && pl->y != 0)
		printf("player position (x, y): (%f, %f)\n", pl->x, pl->y);
	if (pl->dirX != 0 || pl->dirY != 0)
		printf("player direction (x, y): (%f, %f)\n", pl->dirX, pl->dirY);
	if (pl->walk != 0)
		printf("walk direction (-1 or 0 or 1): (%d)\n", pl->walk);
	if (pl->spin != 0)
		printf("spin dir (1=cw, -1=ccw): (%d)\n", pl->spin);
}

void print_map(t_map *map)
{
	int	i;

	printf(YLLW"[map struct]\n"RESET);
	if (map->cols != 0 && map->rows != 0)
		printf("map (rows, cols): (%d, %d)\n", map->rows, map->cols);
	if (map->map)
	{
		i = -1;
		printf("map:\n");
		while (map->map[++i])
			printf("%d:\t[%s]\n", i, map->map[i]);
	}
	if (map->player)
		print_player(map->player);
}

void print_texture(t_texture *tx)
{
	int	i;

	printf(YLLW"[texture struct]\n"RESET);
	printf("wall side textures:\n");
	i = -1;
	while (++i < WALL_SIDES && tx->wall[i] != 0)
		printf("\t%s\n", tx->wall[i]);
	if (tx->floor != -1)
		printf("floor color:\t%lli\n", tx->floor);
	if (tx->ceiling != -1)
		printf("ceiling color:\t%lli\n", tx->ceiling);
}

void	print_cub(t_cub *cub)
{
	printf(YLLW"[cub status]\n"RESET);
	if (cub->fd)
		printf("cub fd:%d\n", cub->fd);
	if (cub->map)
		print_map(cub->map);
	if (cub->textures)
		print_texture(cub->textures);
	
}
