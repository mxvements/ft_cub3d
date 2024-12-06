#include "../includes/cub3d.h"

static char *get_err_msg(int i)
{
	const char	*err_msg[WALL_SIDES + 2] = {
		ERR_TXT_NORTH,
		ERR_TXT_SOUTH,
		ERR_TXT_WEST,
		ERR_TXT_EAST,
		ERR_COL_F,
		ERR_COL_C
	} ;
	if (i > (WALL_SIDES + 2))
		return (NULL);
	return ((char *)err_msg[i]);
}

static char *get_prefix(int i)
{
	const char	*prefix[WALL_SIDES + 2] = {
		"NO",
		"SO",
		"WE",
		"EA",
		"F",
		"C"
	} ;
	return ((char *)prefix[i]);
}

// static int save_texture()
// {
// 	return (0);
// }

// static int save_color()
// {
// 	return (0);
// }

int parse_texture_and_colors(t_texture *tx, int fd)
{
	char 	*line;
	char	*prefix;
	char 	*err_msg;
	int		j;
	int		i;
	
	i= -1;
	while (++i < (WALL_SIDES + 2))
	{
		line = get_next_line(fd);
		if (!line)
			return (-1); //error de archivo
		j = -1;
		while (++j < WALL_SIDES + 2)
		{
			prefix = get_prefix(j);
			err_msg = get_err_msg(j);
			//case of wall's textures
			if (j < WALL_SIDES && ft_strncmp(prefix, line, 2) == 0)
			{
				if (check_file_extension(line, ".xpm\n") < 0)
					print_error(err_msg); //ERROR, should return
				tx->wall[j] = line;
				printf("side: %d\t filepath:%s\n", j, line);
			}
			//case of plane's colors
			else if (j >= WALL_SIDES && ft_strncmp(prefix, line, 1) == 0)
			{
				char **rgb = ft_split(line + 2, ',');
				if (check_color(rgb) < 0)
					print_error(ERR_COL); //ERROR
				printf("plane side: %d\tarray_len del rgb:%d\n", j, strarr_len(rgb));
				strarr_print(rgb);
				//convert string to int, and then to hex nbr
				long long color = color_str_to_long(rgb);
				if (j == 4) //floor
					tx->floor = color;
				else
					tx->ceiling = color;
			}
		}
	}
	return (0);
}