#include "../includes/cub3d.h"

/**
 * @brief Function to set all rows to max length of the map, filling with ' ' on
 * empty spaces
 *
 * @return int
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

static int	get_player(t_map *map, char *line, int row)
{
	char		*player;
	const char	dir[4] = {'N', 'S', 'E', 'W'};
	const int	vector[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {-1, 0}};
	int			i;

	i = -1;
	while (dir[++i])
	{
		player = ft_strchr(line, dir[i]);
		if (player && is_player(map->player) == 1)
			return (print_error("get_player", ERR_PL_MULT));
		if (player)
		{
			map->player->x = row;
			map->player->y = player - line; // check this
			map->player->dirX = vector[i][0];
			map->player->dirY = vector[i][1];
			return (0);
		}
	}
	return (1);
}

static int	get_map(t_map *map, int fd)
{
	size_t	tmp_len;
	char	*tmp;

	while (1)
	{
		tmp = strtrim_gnl(fd, "\t\n");
		if (!tmp)
			break ;
		if (*tmp == '\0')
		{
			free(tmp);
			if (map->rows > 0) // check
				break ; //ERROR, spaces at the end of map
			continue ; //spaces at the start
		}
		tmp_len = is_permitted_char(tmp);
		if (tmp_len < 0)
			return (free(tmp), -1);
		if (get_player(map, tmp, map->rows) < 0)
			return (-1);
		if ((int)tmp_len > map->cols)
			map->cols = (int)tmp_len;
		map->map = strarr_add(map->map, tmp);
		if (!map->map)
			return (print_error("get_map", NULL));
		free(tmp);
		map->rows++;
	}
	return (0);
}

/**
 * @name check_eof
 * @brief Checks the end of file. Spaces, tabs and new lines are accepted as
 * lines after the map reading. If any other char is found in a line, an 
 * error is thrown
 * 
 * @param fd file to read
 * @return int, end status, 0 for OK, -1 for error
 */
static int	check_map_eof(int fd)
{
	char	*line;

	while (1)
	{
		line = strtrim_gnl(fd, "\t\n ");
		if (!line)
			break ;
		if (*line != '\0')
		{
			free(line);
			return (print_error("check_eof", ERR_MAP_END));
		}
		free(line);
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
	if (get_map(map, fd) < 0)
		return (-1);
	// check if there are more lines in the file
	if (check_map_eof(fd) < 0)
		return (-1);
	//all lines the same length, add padding
	if (normalize_map(map) < 0)
		return (-1);
	map->size = PIXEL_SIZE;
	//checks the symbols, {0,1,_}
	if (check_map(map) < 0)
		return (-1);
	return (0);
}
