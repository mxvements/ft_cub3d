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

	if (i >= (WALL_SIDES + 2))
		return (NULL);
	return ((char *)err_msg[i]);
}

static char	*get_prefix(int i)
{
	const char	*prefix[WALL_SIDES + 2] = {"NO", "SO", "WE", "EA", "F", "C"};

	if (i < (WALL_SIDES + 2))
		return ((char *)prefix[i]);
	return (NULL);
}

static int	save_texture(int j, char *line, t_texture *tx)
{
	char	*filename;
	char	*prefix;
	char	*err_msg;

	err_msg = get_err_msg(j);
	prefix = get_prefix(j);
	if (ft_strncmp(prefix, line, 2) != 0)
		return (0);
	if (check_file_extension(line, ".xpm") < 0)
		return (print_error("save_texture", err_msg));
	filename = ft_strtrim(line + 2, "\t ");
	if (!filename)
		return (print_error("save_texture", NULL));
	tx->wall[j] = filename;
	return (0);
}

/**
 * TODO: check for 0,0,0
 */
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
		return (print_error("save_color", NULL));
	if (check_color(rgb) < 0)
		return (print_error("save_color", err_msg));
	color = color_str_to_long(rgb);
	if (j == 4)
		tx->floor = color;
	else
		tx->ceiling = color;
	strarr_freenull(&rgb);
	return (0);
}

int	parse_texture_and_colors(t_texture *tx, int fd)
{
	char	*line;
	int		i;

	while (1)
	{
		if (is_texture_struct_full(tx) == 1)
			break ;
		line = strtrim_gnl(fd, "\t\n ");
		if (!line)
			return (print_error("parse_texture_and_colors", NULL));
		i = -1;
		while (++i < WALL_SIDES + 2 && *line != '\0')
		{
			if (i < WALL_SIDES && save_texture(i, line, tx) < 0)
				return (-1);
			else if (i >= WALL_SIDES && save_color(i, line, tx) < 0)
				return (-1);
		}
		free(line);
	}
	return (0);
}
