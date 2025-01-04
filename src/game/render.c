#include "../includes/cub3d.h"

void	set_image_pixel(t_img *image, int x, int y, int color)
{
	int	pixel;

	pixel = y * (image->size_line / 4) + x;
	image->addr[pixel] = color;
}

static void	set_frame_image_pixel(t_cub *data, t_img *image, int x, int y)
{
	if (data->texture_pixels[y][x] > 0)
		set_image_pixel(image, x, y, data->texture_pixels[y][x]);
	else if (y < data->map->rows / 2)
		set_image_pixel(image, x, y, data->textures->ceiling);
	else if (y < data->map->rows -1)
		set_image_pixel(image, x, y, data->textures->floor);
}

void	render_frame(t_cub *data)
{
	t_img	image;
	int		x;
	int		y;

	image.img = NULL;
	init_img(data, &image, data->map->cols, data->map->rows);
	y = 0;
	while (y < data->map->rows)
	{
		x = 0;
		while (x < data->map->cols)
		{
			set_frame_image_pixel(data, &image, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->win, image.img, 0, 0);
	mlx_destroy_image(data->mlx->mlx, image.img);
}