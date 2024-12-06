/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printMap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlu <zlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:30:06 by zlu               #+#    #+#             */
/*   Updated: 2024/12/06 16:24:20 by zlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_game.h"

void	insect_img(t_data *data, t_map_game *map)
{
	int		i;
	int		j;
	char	**res;

	i = 0;
	res = map->map2d;
	testprintMap(res);
	while(i<data->size)
	{
		j = 0;
		while(j<data->size)
		{
			mlx_pixel_put(data->mlx, data->win, i, j, 0x00FF0000);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->map->img_pared, data->size, data->size);
	printf("hola\n");
	// while (res[i])
	// {
	// 	j = 0;
	// 	while (res[i][j])
	// 	{
	// 		mapok(res, data, i, j);
	// 		j++;
	// 	}
	// 	i++;
	// }
}

void	mapok(char **res, t_data *data, int i, int j)
{
	// int x = 0;

	
	 printf("i -> %d , j-> %d y data-> %c y longitud-> %d.\n", i, j, res[i][j], data->size);
	if (res[i][j] == '1')
	{
		// while (x < data->size)
		// {
		// 	mlx_pixel_put(data->mlx, data->win, (i*data->size)+x, (j*data->size)+x, 0xFFFFFF);
		// 	x++;
		// 	/* code */
		// }
		
		// printf("aqui1\n");
		// mlx_pixel_put(data->mlx, data->win, i, j, 0x000000);
		// mlx_put_image_to_window(data->mlx, data->win, data->map->img_pared, j * data->size, i * data->size);
		// printf("aqui2\n");
		
	}
	if (res[i][j] == 'P')
		// while (x < data->size)
		// {
		// 	mlx_pixel_put(data->mlx, data->win, (i*data->size)+x, (j*data->size)+x, 0xFF00FF);
		// 	x++;
		// 	/* code */
		// }
		// mlx_pixel_put(data->mlx, data->win, i, j, 0xFF00FF);
		// mlx_put_image_to_window(data->mlx, data->win,
			// data->map->img_people, j * data->size, i * data->size);
	if (res[i][j] != '1'){
		// printf("aqui mapok\n");
		// while (x < data->size)
		// {
		// 	mlx_pixel_put(data->mlx, data->win, (i*data->size)+x, (j*data->size)+x, 0x000000);
		// 	x++;
		// 	/* code */
		// }
		
		// mlx_put_image_to_window(data->mlx, data->win,
			// data->map->img_arena, j * data->size, i * data->size);
	}
}

void	ini(t_data *data)
{
	int	img_size[2];

	img_size[0] = 128;
	img_size[1] = 128;
	data->map->path_pared = "../../textures/pared.xpm";
	printf("path->%s.\n", data->map->path_pared);
	// data->map->path_arena = "../../textures/arena.xpm";
	// data->map->path_aladin = "../../textures/aladin.xpm";
	data->map->img_pared = mlx_xpm_file_to_image(data->mlx, data->map->path_pared, &img_size[0], &img_size[1]);
	printf("img->%p.\n", data->map->img_pared );
	// data->map->img_arena = mlx_xpm_file_to_image(data->mlx,
	// 		data->map->path_arena, &img_size[0], &img_size[1]);
	// data->map->img_people = mlx_xpm_file_to_image(data->mlx,
	// 		data->map->path_aladin, &img_size[0], &img_size[1]);

}

void	print_map_game(t_data *data, t_map_game *map)
{
	mlx_clear_window(data->mlx, data->win);
	insect_img(data, map);
}
