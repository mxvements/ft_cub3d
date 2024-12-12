#include "../includes/cub3d.h"

static void	strip_line(char **src, size_t src_len, char c)
{
	int		i;
	char 	*tmp;

	i = -1;
	tmp = *src;
	while (--src_len >= 0 && tmp[src_len] == c)
		tmp[src_len] = '\0';
}

static int strjoin_free(char **dst, char **s)
{
	char *tmp;
	char *s1;
	char *s2;

	s1 = *dst;
	s2 = *s;
	tmp = ft_strdup(s1);
	if (!tmp)
		return (print_error(NULL));
	free(s1);
	s1 = ft_strjoin(tmp, s2);
	if (!s1)
		return (free(tmp), print_error(NULL));
	free(tmp);
	return (0);
}

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
		strip_line(&(map->map[i]), len, '\n');
		if (len == map->cols)
			continue ;
		padding_len = map->cols - len;
		padding = (char *)ft_calloc(1, sizeof(char) * (map->cols - len + 1));
		if (!padding)
			return (print_error(NULL));
		padding[padding_len] = '\0';
		ft_memset((void *)padding, ' ', padding_len);
		if (strjoin_free(&(map->map[i]), &padding) < 0)
			return (-1);
	}
	return (0);
}

static int	get_player(t_map *map, char *line, int row)
{
	char		*player;
	const char	dir[4] = {'N', 'S', 'E', 'W'};
	const int	vector[4][2] = {{-1,0}, {1,0}, {0,1}, {-1,0}};
	int			i;

	i = -1;
	while (dir[++i])
	{
		player =  ft_strchr(line, dir[i]);
		if (player)
		{
			map->player->x = row;
			map->player->y = player - line; //check this
			map->player->dirX = vector[i][0];
			map->player->dirY = vector[i][1];
			return (0);
		}
	}
	return (-1);
}

static int get_map(t_map *map, int fd)
{
	size_t	tmp_len;
	char	*tmp;

	while (1)
	{
		tmp = get_next_line(fd);
		if (!tmp)
			break ;
		tmp_len = check_permitted_char(tmp);
		if (tmp_len < 0)
			return (free(tmp), -1);
		get_player(map, tmp, map->rows);
		if ((int)tmp_len > map->cols)
			map->cols = (int)tmp_len;
		map->map = strarr_add(map->map, tmp);
		if (!map->map)
			return (print_error(NULL));
		free(tmp);
		map->rows++;
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
	map->map = (char **)ft_calloc(1, sizeof(char *));
	if (!map->map)
		return (print_error(NULL));
	if (get_map(map, fd) < 0)
		return (-1);
	if (normalize_map(map) < 0)
		return (-1);
	if (check_map(map) < 0)
		return (-1);
	return (0);
}
