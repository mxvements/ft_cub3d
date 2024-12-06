#include "../includes/cub3d.h"

// static int parse_map_to_int(t_map *map, char **src)
// {
// 	int i;
// 	int j;

	
// }

int	parse_map(t_map *map, int fd)
{
	char *tmp;
	char **tmp_map;

	tmp_map = (char **)ft_calloc(1, sizeof(char *));
	if (!tmp_map)
		return (print_error(NULL)); //error de malloc
	while (1)
	{
		tmp = get_next_line(fd);
		if (!tmp)
			break ;
		tmp_map = strarr_add(tmp_map, tmp);
		if (!tmp_map)
			return (-1);
	}
	//convert char to number, delete '\t'
	if (parse_map_to_int(map, tmp_map) < 0)
		return (-1);
	//check map
	if (check_map(map->map) < 0)
		return (-1);
	return (0);
}
