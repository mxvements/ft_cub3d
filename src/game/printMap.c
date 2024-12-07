
#include "../includes/cub3d_game.h"

void	insect_img(t_data *data, t_map_game *map)
{
	int		i;
	int		j;
	char	**res;

	i = 0;
	res = map->map2d;
	testprintMap(res);
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

void	mapok(char **res, t_data *data, int i, int j)
{
	if (res[i][j] != '1')
	{
		// while (x < data->size)
		// {
		// 	mlx_pixel_put(data->mlx, data->win, (i*data->size)+x, (j*data->size)+x, 0x000000);
		// 	x++;
		// 	/* code */
		// }
		// mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0, 0);
		
		mlx_put_image_to_window(data->mlx, data->win,
			data->map->img_arena, j * data->size, i * data->size);
	}
	if (res[i][j] == '1')
	{
		// while (x < data->size)
		// {
		// 	mlx_pixel_put(data->mlx, data->win, (i*data->size)+x, (j*data->size)+x, 0xFFFFFF);
		// 	x++;
		// 	/* code */
		// }

		mlx_put_image_to_window(data->mlx, data->win, data->map->img_pared, j * data->size, i * data->size);
		
	}
	if (res[i][j] == 'P')
		// while (x < data->size)
		// {
		// 	mlx_pixel_put(data->mlx, data->win, (i*data->size)+x, (j*data->size)+x, 0xFF00FF);
		// 	x++;
		// 	/* code */
		// }
		mlx_put_image_to_window(data->mlx, data->win,
			data->map->img_people, j * data->size, i * data->size);
}

void	ini(t_data *data)
{
	int	img_size[2];

	img_size[0] = 32;
	img_size[1] = 32;
	data->map->path_pared = "./textures/pared.xpm";
	data->map->path_arena = "./textures/arena.xpm";
	data->map->path_aladin = "./textures/aladin.xpm";
	data->map->img_pared = mlx_xpm_file_to_image(data->mlx,
			data->map->path_pared, &img_size[0], &img_size[1]);
	data->map->img_arena = mlx_xpm_file_to_image(data->mlx,
			data->map->path_arena, &img_size[0], &img_size[1]);
	data->map->img_people = mlx_xpm_file_to_image(data->mlx,
			data->map->path_aladin, &img_size[0], &img_size[1]);

}

void	print_map_game(t_data *data, t_map_game *map)
{
	// t_data_img	img;
	mlx_clear_window(data->mlx, data->win);
	// img.img = mlx_new_image(data->mlx, 1920, 1080);
	// data->img->img = img.img;
	// data->img->addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
	// 							&img.endian);
	insect_img(data, map);
}
