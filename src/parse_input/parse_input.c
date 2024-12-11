#include "../includes/cub3d.h"



/**
 * Check map:
 * - should have the extension .cub
 * - textures should have extension .xpm
 * - floor and ceiling should be colors (hex numbers)
 * - map -> all 0 should be surrounded by 0 or 1, all spaces should be surrounded by 1
 */
int	parse_input(t_cub *cub, char *filepath)
{
	t_map		*map;
	t_texture	*texture;

	map = cub->map;
	texture = cub->textures;
	cub->fd = open(filepath, O_RDONLY);
	if (cub->fd < 0)
		return (-1);
	if (parse_texture_and_colors(texture, cub->fd) < 0)
		return (-1);
	if (parse_map(map, cub->fd) < 0)
		return (-1); //TODO: return -1 in case of error, must handle it here
	//just to check:
	// printf("map length: %d\n", strarr_len(map->map));
	close(cub->fd);
	return (0);
}
