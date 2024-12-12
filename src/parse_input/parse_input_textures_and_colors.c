#include "../includes/cub3d.h"

static char	*get_err_msg(int i)
{
	const char	*err_msg[WALL_SIDES + 2] = {
		ERR_TXT_NORTH,
		ERR_TXT_SOUTH,
		ERR_TXT_WEST,
		ERR_TXT_EAST,
		ERR_COL_F,
		ERR_COL_C
	};

	if (i > (WALL_SIDES + 2))
		return (NULL);
	return ((char *)err_msg[i]);
}

static char	*get_prefix(int i)
{
	const char	*prefix[WALL_SIDES + 2] = {"NO", "SO", "WE", "EA", "F", "C"};

	return ((char *)prefix[i]);
}
/**
 * TODO: check if the texture/color is already saved
 */
static int	save_texture(int j, char *line, t_texture *tx)
{
	char	*prefix;
	char	*err_msg;

	err_msg = get_err_msg(j);
	prefix = get_prefix(j);
	if (ft_strncmp(prefix, line, 2) != 0)
		return (0);
	if (check_file_extension(line, ".xpm\n") < 0)
		return (print_error(err_msg));
	tx->wall[j] = line;
	// printf("side: %d\t filepath:%s\n", j, line); // LOG
	return (0);
}

static int	save_color(int j, char *line, t_texture *tx)
{
	char		*prefix;
	char		*err_msg;
	char		**rgb;
	long long	color;

	err_msg = get_err_msg(j);
	prefix = get_prefix(j);
	if (ft_strncmp(prefix, line, 1) != 0)
		return (0);
	rgb = ft_split(line + 2, ',');
	if (!rgb)
		return (print_error(NULL));
	if (check_color(rgb) < 0)
		return (print_error(err_msg));
	// printf("plane side: %d\tarray_len del rgb:%d\n", j, strarr_len(rgb)); // LOG
	// strarr_print(rgb);                                                    // LOG
	color = color_str_to_long(rgb);
	if (j == 4)
		tx->floor = color;
	else
		tx->ceiling = color;
	return (0);
}

int	parse_texture_and_colors(t_texture *tx, int fd)
{
	char	*line;
	int		j;
	int		i;

	i = -1;
	//lines that are either wall textures or plane colors
	while (++i < (WALL_SIDES + 2))
	{
		line = get_next_line(fd);
		if (!line)
			return (-1); // ending of file, error de archivo
		j = -1;
		while (++j < WALL_SIDES + 2)
		{
			if (j < WALL_SIDES && save_texture(j, line, tx) < 0)
				return (-1);
			else if (j >= WALL_SIDES && save_color(j, line, tx) < 0)
				return (-1);
		}
	}
	return (0);
}
