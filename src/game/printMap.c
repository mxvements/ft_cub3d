
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
			data->minimap->img_floor, (j * (data->map->size/4)) , (i * (data->map->size/4))+(6 * data->map->size)); // entre 4, porque imagen es 4 veces menor que el tañamo de ventana, y se multiplica 7,5 para que centre abajo, aunque seria 7,5 para se exactos
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
		mlx_put_image_to_window(data->mlx->mlx_ptr, data->mlx->win, data->minimap->img_wall, (j * (data->map->size/4)),(i * (data->map->size/4))+(6 * data->map->size));
		
	}
	if (res[i][j] == 'N' || res[i][j] == 'S' ||res[i][j] == 'W' || res[i][j] == 'W')
		// while (x < data->size)
		// {
		// 	mlx_pixel_put(data->mlx, data->win, (i*data->size)+x,
				// (j*data->size)+x, 0xFF00FF);
		// 	x++;
		// 	/* code */
		// }
		mlx_put_image_to_window(data->mlx->mlx_ptr, data->mlx->win,
			data->minimap->img_player, (j * (data->map->size/4)),(i * (data->map->size/4))+(6 * data->map->size));
}

void	init_minimap(t_cub *data)
{
	t_minimap *minimap;

	minimap = malloc(sizeof(t_minimap));

	int	img_size[2];

	img_size[0] = IMG_SIZE_X;
	img_size[1] = IMG_SIZE_Y;
	minimap->path_wall = "./textures/pared_mini.xpm";
	minimap->path_floor = "./textures/suelo_mini.xpm";
	minimap->path_player = "./textures/pato_mini.xpm";
	minimap->img_wall = mlx_xpm_file_to_image(data->mlx->mlx_ptr, minimap->path_wall, 
			&img_size[0], &img_size[1]);
	minimap->img_floor = mlx_xpm_file_to_image(data->mlx->mlx_ptr, minimap->path_floor, 
			&img_size[0], &img_size[1]);
	minimap->img_player = mlx_xpm_file_to_image(data->mlx->mlx_ptr, minimap->path_player,
			&img_size[0], &img_size[1]);

	data->minimap = minimap;
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
