#include "../includes/cub3d.h"

/**
 * TODO: on strarr_add, check protections
 */

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

static long long	color_convert(char **rgb)
{
	long long	color;
	int		c;
	int		i;

	color = 0;
	c = 3;
	i = -1;
	while (rgb[++i])
	{
		c--;
		color += ft_atoi(rgb[i]) << (8 * c);
	}
	printf("color: %lld\n", color);
	return (color);
}

void	strarr_print(char **str)
{
	int	i = -1;
	while (str[++i])
	{
		printf("%s\n", str[i]);
	}
}

static int parse_texture(t_texture *tx, int fd)
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
				if (!rgb)
					return (-1);//error
				printf("plane side: %d\tarray_len del rgb:%d\n", j, strarr_len(rgb));
				strarr_print(rgb);
				//convert string to int, and then to hex nbr
				long long color = color_convert(rgb);
				if (j == 4) //floor
					tx->floor = color;
				else
					tx->ceiling;
			}
		}
	}
	return (0);
}

/**
 * Check map:
 * - should have the extension .cub
 * - textures should have extension .xpm
 * - floor and ceiling should be colors (hex numbers)
 * - map -> all 0 should be surrounded by 0 or 1, all spaces should be surrounded by 1
 */
t_cub	*parse_input(t_cub *cub, char *filepath)
{
	t_map		*map;
	t_texture	*texture;

	map = cub->map;
	texture = cub->textures;
	map->fd = open(filepath, O_RDONLY);
	if (map->fd < 0)
		return (NULL); //will need to free map and print the proper err message, errno is set
	//read, the 1sr 6 lines are textures, then the map
	if (parse_texture(texture, map->fd) < 0)
		return (NULL);

	// //then, get the rest, which is the map
	char *tmp;
	map->map = (char **)ft_calloc(1, sizeof(char *));
	while (1)
	{
		tmp = get_next_line(map->fd);
		if (!tmp)
			break ;
		map->map = strarr_add(map->map, tmp);
		if (!map->map)
			return (NULL);
	}
	//just to check:
	printf("map length: %d\n", strarr_len(map->map));
	close(map->fd);
	return (cub);
}
