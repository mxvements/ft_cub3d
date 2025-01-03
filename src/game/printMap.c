
#include "../includes/cub3d.h"

// void	insert_img(t_cub *data, t_map *map)
// {
// 	int		i;
// 	int		j;
// 	char	**res;

// 	i = 0;
// 	res = map->map;
// 	// testprintMap(res);
// 	while (res[i])
// 	{
// 		j = 0;
// 		while (res[i][j])
// 		{
// 			mapok(res, data, i, j);
// 			j++;
// 		}
// 		i++;
// 	}
// }

// void	mapok(char **res, t_cub *cub, int i, int j)
// {
// 	const int	f_div = 4;
// 	const int 	f_mult = 1;

// 	if (res[i][j] == ' ')
// 	{
// 		mlx_put_image_to_window(
// 			cub->mlx->mlx_ptr, 
// 			cub->mlx->win,
// 			cub->minimap->img_void, 
// 			(j * (cub->map->size / f_div)), 
// 			(i * (cub->map->size / f_div)) + (f_mult * cub->map->size));
// 	}
// 	if (res[i][j] == '0')
// 	{
// 		mlx_put_image_to_window(
// 			cub->mlx->mlx_ptr, 
// 			cub->mlx->win,
// 			cub->minimap->img_floor, 
// 			(j * (cub->map->size / f_div)), 
// 			(i * (cub->map->size / f_div)) + (f_mult * cub->map->size));
// 		/* entre 4,
// 		porque imagen es 4 veces menor que el tañamo de ventana,
// 		y se multiplica 7,5 para que centre abajo,
// 		aunque seria 7,5 para se exactos*/
// 	}
// 	if (res[i][j] == '1')
// 	{
// 		mlx_put_image_to_window(
// 			cub->mlx->mlx_ptr, 
// 			cub->mlx->win,
// 			cub->minimap->img_wall, 
// 			(j * (cub->map->size / f_div)), 
// 			(i * (cub->map->size / f_div)) + (f_mult * cub->map->size));
// 	}
// 	if (res[i][j] == 'N' || res[i][j] == 'S' || res[i][j] == 'W'
// 		|| res[i][j] == 'W')
// 		mlx_put_image_to_window(
// 			cub->mlx->mlx_ptr, 
// 			cub->mlx->win,
// 			cub->minimap->img_player, 
// 			(j * (cub->map->size / f_div)), 
// 			(i * (cub->map->size / f_div)) + (f_mult * cub->map->size));
// }

void	render_map(t_cub *cub, t_map *map)
{
	(void)map;
	mlx_clear_window(cub->mlx->mlx_ptr, cub->mlx->win);
	render_minimap(cub);
}
