#include "../includes/cub3d.h"

int	is_file_extension(char *filepath, char *extension)
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
	return (0);
}

int	is_color(char **rgb)
{
	const int	arr_len = 3;
	int			i;
	int			tmp_col;
	if (!rgb || strarr_len(rgb) != arr_len)
		return (-1);
	i = -1;
	while (++i < arr_len && rgb[i])
	{
		tmp_col = ft_atoi(rgb[i]);
		if (tmp_col < 0 || tmp_col > 255)
			return (-1);
	}
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
int	is_permitted_char(char *line)
{
	const char	permitted[9] = {' ', '0', '1', '\n', '\t', 'N', 'E', 'S', 'W'};
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
			return (print_error("check_permitted_char", ERR_MAP_CHAR));
	}
	return (i);
}

int	is_texture_struct_full(t_texture *tx)
{
	int	i;

	i = -1;
	while (++i < WALL_SIDES)
	{
		if (tx->wall[i] == NULL || *tx->wall[i] == '\0')
			return (0);
	}
	if (tx->ceiling == -1 || tx->floor == -1) //what if the colorss are 0
		return (0);
	return (1);
}

int	is_player(t_player *player)
{
	if (player->x == -1 || player->y == -1)
		return (0);
	return (1);
}