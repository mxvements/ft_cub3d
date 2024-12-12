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

void free_map(t_map *map)
{
	if (map->map)
		strarr_freenull(&map->map); //TODO: revisar esta funcion
	if (map->player)
	{
		free(map->player); //it just has floats and int
		map->player = NULL;
	}
}

static void free_texture(t_texture *texture)
{
	int	i ;

	i = -1;
	while (++i < WALL_SIDES && texture->wall[i] != 0)
		ft_freenull(&texture->wall[i]);
}

/* cub is never mallocked, we just need to free the nested structs */
int free_cub(t_cub *cub)
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
