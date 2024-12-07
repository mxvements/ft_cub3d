#include "../includes/cub3d.h"

/**
 * @brief Function to set all rows to max length of the map, filling with ' ' on
 * empty spaces
 * 
 * @return int 
 */
static int normalize_map()
{

}
/**
 * @brief Read file line by line (after textures and colors lines), checking
 * each time for the length (cols), and the permitted chars. A the end, sets the 
 * final length of the map (rows) and checks for the map to be compliant with 
 * the rules of the subject
 * 
 * @param map 
 * @param fd 
 * @return int 
 */
int	parse_map(t_map *map, int fd)
{
	char 	*tmp;
	size_t	tmp_len;

	map->map = (char **)ft_calloc(1, sizeof(char *));
	if (!map->map)
		return (print_error(NULL));
	while (1)
	{
		tmp = get_next_line(fd);
		if (!tmp)
			break ;
		map->rows++;
		tmp_len = check_permitted_char(tmp);
		if (tmp_len < 0)
			return (-1);
		if ((int)tmp_len > map->cols)
			map->cols = (int)tmp_len;
		map->map= strarr_add(map->map, tmp);
		if (!map->map)
			return (print_error(NULL));
		free(tmp);
	}
	printf("Map dims: [%d, %d]\n", map->rows, map->cols);
	/*check map*/
	if (check_map(map) < 0)
		return (-1);
	return (0);
}
