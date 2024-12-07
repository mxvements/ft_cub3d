#include "../includes/cub3d.h"

int	check_file_extension(char *filepath, char *extension)
{
	const int	ext_len = ft_strlen(extension);
	const int	path_len = ft_strlen(filepath);
	const int	start = path_len - ext_len;
	int			i;

	i = 0;
	// printf("%s\n", filepath + start);
	while (filepath[start + i])
	{
		if (filepath[start + i] - extension[i] != 0)
			return (-1);
		i++;
	}
	mlx_init();
	return (0);
}

int	check_color(char **rgb)
{
	if (!rgb || strarr_len(rgb) != 3)
		return (-1);
	return (0);
}

/**
 * @brief Function that takes the line to append to the map and checks if all
 * the chars contained are permitted by the program:
 * 
 * + chars of map:		' ', '0', '1','\n'
 * 
 * + chars  of player:	'N','E','S','W'
 * 
 * @param line 
 * @return int length evaluated
 */
int	check_permitted_char(char *line)
{
	const char	permitted[9] = {' ', '0', '1', '\n', 'N', 'E', 'S', 'W'};
	int 		i;
	int 		j;
	int			flag;

	i = -1;
	flag = 0;
	while (line[++i])
	{
		j = -1;
		while (permitted[++j])
		{
			if (line[i] == permitted[j])
			{
				flag = 0;
				break ;
			}
			if (line[i] != permitted[j])
				flag = 1;
		}
		if (flag == 1)
		{
			printf("Error on %s, on idx: %d\n", line, i);
			return (print_error(ERR_MAP_CHAR));
		}
	}
	return (i);
}