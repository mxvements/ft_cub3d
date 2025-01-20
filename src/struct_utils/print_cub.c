#include "../includes/cub3d.h"

void	print_player(t_player *pl)
{
	printf(YLLW "\n[player status]\n" RESET);
	if (pl->map_x != -1 && pl->map_y != -1)
		printf("player position (x, y): (%f, %f)\n", pl->map_x, pl->map_y);
	if (pl->angle)
		printf("player angle in rads: (%f)\n", pl->angle);
}

void	print_map(t_map *map)
{
	int	i;

	printf(YLLW "\n[map status]\n" RESET);
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

void	print_texture(t_texture *tx)
{
	int	i;

	printf(YLLW "\n[texture status]\n" RESET);
	printf("wall side textures:\n");
	i = -1;
	while (++i < WALL_SIDES && tx->wall[i] != 0)
		printf("\t%s\n", tx->wall[i]);
	if (tx->floor != -1)
		printf("floor color:\t%lli\n", tx->floor);
	if (tx->ceiling != -1)
		printf("ceiling color:\t%lli\n", tx->ceiling);
}

void	print_minimap(t_minimap *minimap)
{
	printf(YLLW "\n[minimap status]\n" RESET);
	if (minimap->start_x != 0)
		printf("start row position minimap: %f\n", minimap->start_x);
	if (minimap->img_wall)
		printf("img_wall: %p\n", minimap->img_wall);
	if (minimap->img_void)
		printf("img_void: %p\n", minimap->img_void);
	if (minimap->img_player)
		printf("img_player: %p\n", minimap->img_player);
	if (minimap->img_floor)
		printf("img_floor: %p\n", minimap->img_floor);
}
void print_options_status(t_options *options)
{
	printf(YLLW "\n[options status]\n" RESET);
	printf("wall collisions\t %d\n", options->wall_col);
	printf("show minimap\t %d\n", options->show_minimap);
	printf("move speed\t %f\n", options->move_speed);
	printf("rotate speed\t %f\n", options->rotate_speed);
}

void	print_cub(t_cub *cub)
{
	printf(YLLW "\n[cub status]\n" RESET);
	if (cub->fd)
		printf("cub fd:%d\n", cub->fd);
	if (cub->map)
		print_map(cub->map);
	if (cub->textures)
		print_texture(cub->textures);
	if (cub->minimap)
		print_minimap(cub->minimap);
}
