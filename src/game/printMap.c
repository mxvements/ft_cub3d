
#include "../includes/cub3d.h"

void	insert_img(t_cub *data, t_map *map)
{
	int		i;
	int		j;
	char	**res;

	i = 0;
	res = map->map;
	// testprintMap(res);
	while (res[i])
	{
		j = 0;
		while (res[i][j])
		{
			mapok(res, data, i, j);
			j++;
		}
		i++;
	}
}

void	mapok(char **res, t_cub *data, int i, int j)
{
	if (res[i][j] != '1')
	{
		mlx_put_image_to_window(data->mlx->mlx_ptr, data->mlx->win,
			data->minimap->img_floor, (j * (data->map->size / 4)), (i
				* (data->map->size / 4)) + (6 * data->map->size));
		/* entre 4,
		porque imagen es 4 veces menor que el tañamo de ventana,
		y se multiplica 7,5 para que centre abajo,
		aunque seria 7,5 para se exactos*/
	}
	if (res[i][j] == '1')
	{
		mlx_put_image_to_window(data->mlx->mlx_ptr, data->mlx->win,
			data->minimap->img_wall, (j * (data->map->size / 4)), (i
				* (data->map->size / 4)) + (6 * data->map->size));
	}
	if (res[i][j] == 'N' || res[i][j] == 'S' || res[i][j] == 'W'
		|| res[i][j] == 'W')
		mlx_put_image_to_window(data->mlx->mlx_ptr, data->mlx->win,
			data->minimap->img_player, (j * (data->map->size / 4)), (i
				* (data->map->size / 4)) + (6 * data->map->size));
}

void	render_map(t_cub *data, t_map *map)
{
	mlx_clear_window(data->mlx->mlx_ptr, data->mlx->win);
	insert_img(data, map);
}
