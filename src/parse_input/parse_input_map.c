#include "../includes/cub3d.h"

// static int	print_map(t_map *map)
// {
// 	int i;
// 	int j;

// 	i = -1;
// 	while (map->map[++i])
// 	{

// 	}
// }


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
