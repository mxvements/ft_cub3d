#include "../includes/cub3d.h"

/**
 * @brief Function to set all rows to max length of the map, filling with ' ' on
 * empty spaces. This 'normalization' allow us to access any map location
 * avoiding segfaults. *
 *
 * @param map
 * @return int, status error,
 *		0: OK
 *		-1: Error (parsing err or initialization err)
 */
static int	normalize_map(t_map *map)
{
	int		i;
	int		len;
	char	*padding;
	int		padding_len;

	i = -1;
	while (map->map[++i])
	{
		len = ft_strlen(map->map[i]);
		if (len == map->cols)
			continue ;
		padding_len = map->cols - len;
		padding = (char *)ft_calloc(1, sizeof(char) * (padding_len + 1));
		if (!padding)
			return (print_error("normalize_map", NULL));
		padding[padding_len] = '\0';
		ft_memset((void *)padding, ' ', padding_len);
		map->map[i] = ft_strjoin_free(&(map->map[i]), &padding);
		if (!map->map[i])
			return (-1);
		free(padding);
	}
	return (0);
}

/**
 * @brief Get the player object, with its position, and direction vector.
 * This function checks for multiple instances of player and returns the
 * custom error in that case.
 *
 * @param map
 * @param line
 * @param row
 * @return int, error status,
 * 		0: OK,
 * 		-1: error (parse or initialization)
 */
static int	get_player(t_map *map, char *line, int row)
{
	char		*player;
	const char	dir[4] = {'S', 'E', 'N', 'W'};
	int			i;

	i = -1;
	while (++i < 4)
	{
		player = ft_strchr(line, dir[i]);
		if (player && is_player(map->player) == 1)
			return (print_error("get_player", ERR_PL_MULT));
		if (player)
		{
			map->player->map_x = row;
			map->player->map_y = player - line;
			map->player->angle = (PI * i)/2;
			return (0);
		}
	}
	return (1); // TODO: check this, could be a zero
}

static int	get_line_data(t_map *map, char *line)
{
	size_t	line_len;

	line_len = is_permitted_char(line);
	if (line_len < 0)
		return (-1);
	if (get_player(map, line, map->rows) < 0)
		return (-1);
	if ((int)line_len > map->cols)
		map->cols = (int)line_len;
	map->map = strarr_add(map->map, line);
	if (!map->map)
		return (print_error("get_map", NULL));
	return (0);
}

static int	get_map(t_map *map, int fd)
{
	char	*line;

	while (1)
	{
		line = strtrim_gnl(fd, "\t\n");
		if (!line)
			break ;
		if (*line == '\0')
		{
			free(line);
			if (map->rows > 0)
				break ;
			continue ;
		}
		if (get_line_data(map, line) < 0)
			return (free(line), -1);
		free(line);
		map->rows++;
	}
	return (0);
}

/**
 * @brief Read file line by line (after textures and colors lines), checking
 * each time for the length (cols), and the permitted chars. A the end, sets the
 * final length of the map (rows) and checks for the map to be compliant with
 * the rules of the subject,
 * This function 
 * @param map
 * @param fd
 * @return int
 */
int	parse_map(t_map *map, int fd)
{
	if (get_map(map, fd) < 0)
		return (-1);
	if (!map->map)
		return (print_error("parse_map", ERR_MAP_MISSING));
	if (is_player(map->player) == 0)
		return (print_error("parse_map", ERR_PL_MISSING));
	if (is_player_on_edge(map, map->player) < 0)
		return (-1);
	if (is_map_eof(fd) < 0)
		return (-1);
	if (normalize_map(map) < 0)
		return (-1);
	map->size = PIXEL_SIZE;
	map->old_position = '0';
	if (check_map(map) < 0)
		return (-1);
	return (0);
}
