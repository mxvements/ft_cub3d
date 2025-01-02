
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
		// while (x < data->size)
		// {
		// 	mlx_pixel_put(data->mlx, data->win, (i*data->size)+x,
				// (j*data->size)+x, 0x000000);
		// 	x++;
		// 	/* code */
		// }
		// mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0, 0);
		mlx_put_image_to_window(data->mlx->mlx_ptr, data->mlx->win,
			data->minimap->img_floor, (j * (data->map->size / 4)), (i
				* (data->map->size / 4)) + (7 * data->map->size));
		/*	entre 4, porque imagen es 4 veces menor que el tañamo de
			ventana, y se multiplica 7,5 para que centre abajo, aunque 
			seria 7,5 para se exactos
		*/
	}
	if (res[i][j] == '1')
	{
		// while (x < data->size)
		// {
		// 	mlx_pixel_put(data->mlx, data->win, (i*data->size)+x,
				// (j*data->size)+x, 0xFFFFFF);
		// 	x++;
		// 	/* code */
		// }
		mlx_put_image_to_window(data->mlx->mlx_ptr, data->mlx->win,
			data->minimap->img_wall, (j * (data->map->size / 4)), (i
				* (data->map->size / 4)) + (7 * data->map->size));
	}
	if (res[i][j] == 'P')
		// while (x < data->size)
		// {
		// 	mlx_pixel_put(data->mlx, data->win, (i*data->size)+x,
				// (j*data->size)+x, 0xFF00FF);
		// 	x++;
		// 	/* code */
		// }
		mlx_put_image_to_window(data->mlx->mlx_ptr, data->mlx->win,
			data->minimap->img_player, (j * (data->map->size / 4)), (i
				* (data->map->size / 4)) + (7 * data->map->size));
}

void	init_minimap(t_cub *cub)
{
	t_minimap	*minimap;
	int			img_size[2];

	cub->minimap = ft_calloc(1, sizeof(t_minimap));
	if (!cub->minimap)
		return ; // Error
	img_size[0] = IMG_SIZE_X;
	img_size[1] = IMG_SIZE_Y;
	minimap = cub->minimap;
	minimap->path_wall = MINIMAP_WALL;
	minimap->path_floor = "../../textures/suelo_mini.xpm";
	minimap->path_player = MINIMAP_PLAYER;
	//error todo esto da null
	minimap->img_wall = mlx_xpm_file_to_image(
		cub->mlx->mlx_ptr,
		minimap->path_wall, 
		&img_size[0], 
		&img_size[1]
		);
	minimap->img_floor = mlx_xpm_file_to_image(
		cub->mlx->mlx_ptr,
		minimap->path_floor, 
		&img_size[0], 
		&img_size[1]
		);
	minimap->img_player = mlx_xpm_file_to_image(
		cub->mlx->mlx_ptr,
		minimap->path_player, 
		&img_size[0], 
		&img_size[1]
		);
}

void	render_map(t_cub *data, t_map *map)
{
	// t_cub_img	img;
	mlx_clear_window(data->mlx->mlx_ptr, data->mlx->win);
	// img.img = mlx_new_image(data->mlx, 1920, 1080);
	// data->img->img = img.img;
	// data->img->addr = mlx_get_cub_addr(img.img, &img.bits_per_pixel,
			// &img.line_length,
	// 							&img.endian);
	insert_img(data, map);
}
