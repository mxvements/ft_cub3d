#include "../includes/cub3d.h"

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

static void free_minimap(t_minimap *minimap)
{
	if (minimap->img_wall)
		free(minimap->img_wall);
	if (minimap->img_floor)
		free(minimap->img_floor);
	if (minimap->img_player)
		free(minimap->img_player);
	if (minimap->img_void)
		free(minimap->img_void);
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
	if (cub->minimap)
	{
		free_minimap(cub->minimap);
		free(cub->minimap);
		cub->minimap = NULL;
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
