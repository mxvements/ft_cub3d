#include "../includes/cub3d.h"

/**
 * TODO: on strarr_add, check protections
 */

static int parse_texture(t_texture *tx, int fd)
{
	char 		*line;
	int			i;
	const char	*err_msg[WALL_SIDES] = {
		ERR_TXT_NORTH,
		ERR_TXT_SOUTH,
		ERR_TXT_WEST,
		ERR_TXT_EAST
	} ;
	const char	*prefix[WALL_SIDES] = {
		"NO",
		"SO",
		"WE",
		"EA"
	} ;
	printf("enum length: %d\n", WALL_SIDES);

	line = get_next_line(fd);
	if (!line)
		return (-1); //error de archivo
	
	i = 0;
	while (i < WALL_SIDES)
	{
		if (ft_strncmp(prefix[i], line, 2) == 0)
		{
			if (check_file_extension(line, ".xpm") < 0)
				print_error((char *)err_msg[i]); //ERROR, should return
			tx->wall[i] = line;
			printf("side: %d\t filepath:%s\n", i, line);
		}
		i++;
	}
	return (0);
}

/**
 * Check map:
 * - should have the extension .cub
 * - textures should have extension .xpm
 * - floor and ceiling should be colors (hex numbers)
 * - map -> all 0 should be surrounded by 0 or 1, all spaces should be surrounded by 1
 */
t_cub	*parse_input(t_cub *cub, char *filepath)
{
	t_map		*map;
	t_texture	*texture;

	map = cub->map;
	texture = cub->textures;
	map->fd = open(filepath, O_RDONLY);
	if (map->fd < 0)
		return (NULL); //will need to free map and print the proper err message, errno is set
	//read, the 1sr 6 lines are textures, then the map
	if (parse_texture(texture, map->fd) < 0)
		return (NULL);
	// texture->wall[NORTH] = get_next_line(map->fd);
	// texture->wall[SOUTH] = get_next_line(map->fd);
	// texture->wall[WEST] = get_next_line(map->fd);
	// texture->wall[EAST] = get_next_line(map->fd);
	// if (check_textures(texture) < 0)
	// {
	// 	print_error(ERR_TXT);
	// 	return (NULL);
	// }
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
