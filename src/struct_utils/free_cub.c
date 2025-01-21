#include "../includes/cub3d.h"

void	free_map(void *data)
{
	t_map *map;

	map = data;
	if (map->map)
		strarr_freenull(&map->map); // TODO: revisar esta funcion
	if (map->player)
	{
		free(map->player); // it just has floats and int
		map->player = NULL;
	}
}

static void	free_texture(void *data)
{
	t_texture *texture;

	texture = data;
	if (texture->wall[NORTH])
		ft_freenull(&texture->wall[NORTH]);
	if (texture->wall[SOUTH])
		ft_freenull(&texture->wall[SOUTH]);
	if (texture->wall[EAST])
		ft_freenull(&texture->wall[EAST]);
	if (texture->wall[WEST])
		ft_freenull(&texture->wall[WEST]);
}

static void free_minimap(t_mlx *mlx, t_minimap *minimap)
{
	if (minimap->img_wall)
		mlx_destroy_image(mlx->mlx_ptr, minimap->img_wall);
	if (minimap->img_floor)
		mlx_destroy_image(mlx->mlx_ptr, minimap->img_floor);
	if (minimap->img_player)
		mlx_destroy_image(mlx->mlx_ptr, minimap->img_player);
	if (minimap->img_void)
		mlx_destroy_image(mlx->mlx_ptr, minimap->img_void);
}

static void free_mlx(void *data)
{
	t_mlx *mlx;

	mlx = data;
	mlx_destroy_image(mlx->mlx_ptr, mlx->img);
	mlx->img = NULL;
	mlx->img_addr = NULL;
	mlx_destroy_window(mlx->mlx_ptr, mlx->win);
	mlx->win = NULL;
	mlx_destroy_display(mlx->mlx_ptr);
	mlx->mlx_ptr = NULL;
}

static void free_struct(void **s, void(*free_s)(void *))
{
	if (*s)
	{
		free_s(*s);
		free(*s);
		*s = NULL;
	}
}
/* cub is never mallocked, we just need to free the nested structs */
int	free_cub(t_cub *cub)
{	
	if (cub->map)
		free_struct((void **)&cub->map, free_map);
	if (cub->textures)
		free_struct((void **)&cub->textures, free_texture);
	if (cub->minimap)
	{
		free_minimap(cub->mlx, cub->minimap);
		free(cub->minimap);
		cub->minimap = NULL;
	}
	if (cub->mlx) //always last
		free_struct((void **)&cub->mlx, free_mlx);
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
