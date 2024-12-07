#include "../includes/cub3d.h"

/**
 * @brief Function to set all rows to max length of the map, filling with ' ' on
 * empty spaces
 * 
 * @return int 
 */
//TODO: borrar todos los saltos de linea que me matan
static int normalize_map(t_map *map)
{
	int		i;
	int		line_len;
	char 	*padding;
	int		padding_len;
	char	*tmp;

	i = -1;
	while (map->map[++i])
	{
		line_len = ft_strlen(map->map[i]);
		if (line_len == map->cols)
			continue ;
		//if the length is different, then we copy
		padding_len = map->cols - line_len;
		padding = (char *)ft_calloc(1, sizeof(char) * (map->cols - line_len + 1));
		if (!padding)
			return (print_error(NULL));
		padding[padding_len] = '\0';
		ft_memset((void *)padding, ' ', padding_len);
		printf("padding: [%s]\n", padding);
		tmp = ft_strdup(map->map[i]);
		if (!tmp)
			return (print_error(NULL));
		free(map->map[i]);
		map->map[i] = ft_strjoin(tmp, padding);
		if (!map->map[i])
			return (print_error(NULL));
		free(tmp);
		printf("final string: [%s]\n", map->map[i]);
	}
	return (0);
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
	/*normalize map so all rows are the same legth */
	if (normalize_map(map) < 0)
		return (-1);
	/*check map*/
	if (check_map(map) < 0)
		return (-1);
	return (0);
}
