#include "../includes/cub3d.h"



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
	cub->fd = open(filepath, O_RDONLY);
	if (cub->fd < 0)
		return (NULL); //will need to free map and print the proper err message, errno is set
	//read, the 1sr 6 lines are textures, then the map
	if (parse_texture_and_colors(texture, cub->fd) < 0)
		return (NULL);
	if (parse_map(map, cub->fd) < 0)
		return (NULL);
	//just to check:
	printf("map length: %d\n", strarr_len(map->map));
	close(cub->fd);
	return (cub);
}
