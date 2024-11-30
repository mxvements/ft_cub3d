#include "../includes/cub3d.h"

/**
 * Check map:
 * - should have the extension .cub
 */
/**
 * TODO: on strarr_add, check protections
 */
t_cub	*parse_map(t_cub *cub, char *filepath)
{
	t_map		*map;
	t_texture	*texture;

	map = cub->map;
	texture = cub->textures;
	map->fd = open(filepath, O_RDONLY);
	if (map->fd < 0)
		return (NULL); //will need to free map and print the proper err message, errno is set
	//read, the 1sr 6 lines are textures, then the map
	texture->wall[NORTH] = get_next_line(map->fd);
	texture->wall[SOUTH] = get_next_line(map->fd);
	texture->wall[WEST] = get_next_line(map->fd);
	texture->wall[EAST] = get_next_line(map->fd);
	texture->floor = get_next_line(map->fd);
	texture->ceiling = get_next_line(map->fd);
	//then, get the rest, which is the map
	char *tmp;
	map->map = (char **)ft_calloc(1, sizeof(char *));
	while (1)
	{
		tmp = get_next_line(map->fd);
		if (!tmp)
			break ;
		map->map = strarr_add(map->map, tmp);
		if (!map->map)
			return (NULL);
	}
	//just to check:
	printf("map length: %d\n", strarr_len(map->map));
	close(map->fd);
	return (cub);
}
