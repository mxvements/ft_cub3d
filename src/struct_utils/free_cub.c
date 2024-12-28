#include "../includes/cub3d.h"

/** TODO: add to libft */
// void ft_strarr_free(char ***s)
// {
// 	char **arr_s;

// 	arr_s = *s;
// 	while (*arr_s)
// 	{
// 		ft_freenull(*arr_s);
// 		arr_s++;
// 	}
// }

void	free_map(t_map *map)
{
	if (map->map)
		strarr_freenull(&map->map); // TODO: revisar esta funcion
	if (map->player)
	{
		free(map->player); // it just has floats and int
		map->player = NULL;
	}
}

static void	free_texture(t_texture *texture)
{
	if (texture->wall[NORTH])
		ft_freenull(&texture->wall[NORTH]);
	if (texture->wall[SOUTH])
		ft_freenull(&texture->wall[SOUTH]);
	if (texture->wall[EAST])
		ft_freenull(&texture->wall[EAST]);
	if (texture->wall[WEST])
		ft_freenull(&texture->wall[WEST]);
}

/* cub is never mallocked, we just need to free the nested structs */
int	free_cub(t_cub *cub)
{
	if (cub->map)
	{
		free_map(cub->map);
		free(cub->map);
		cub->map = NULL;
	}
	if (cub->textures)
	{
		free_texture(cub->textures);
		free(cub->textures);
		cub->textures = NULL;
	}
	return (0);
}

/**
 * @brief Clean the static variable inside the call of get_next_line
 * This is necessary in oorder not to get 'still reachable' leaks when we have
 * an error mid-file reading.
 * Call this function always before closing the fd
 * @param fd 
 */
void	clean_gnl(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
}
