#include "../includes/cub3d.h"

//este archivo por ahora no lo usamos
void	set_image_pixel(t_image *image, int x, int y, int color)
{
	int	pixel;

	pixel = y * PIXEL_SIZE + x;
	image->addr[pixel] = color;
}

void	set_frame_image_pixel(t_cub *data, t_image *image, int x, int y)
{
	if (data->textures->pixel[y][x] > 0)
		set_image_pixel(image, x, y, data->textures->pixel[y][x]);
	else if (y < WIN_HEIGHT / 2)
		set_image_pixel(image, x, y, data->textures->ceiling);
	else if (y < WIN_HEIGHT -1)
		set_image_pixel(image, x, y, data->textures->floor);
}

void	render_frame(t_cub *data)
{
	t_image	image;
	int		x;
	int		y;

	image.img = NULL;
	init_img(data, &image, WIN_WIDTH, WIN_HEIGHT);
	init_texture_pixels(data);
	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			set_frame_image_pixel(data, &image, x, y);
			x++;
		}
		y++;
	}
}

void	init_texture_pixels(t_cub *data)
{
	int	i;

	data->textures->pixel = ft_calloc(WIN_HEIGHT + 1,
			sizeof * data->textures->pixel);
	if (!data->textures->pixel)
		print_error("pixel", NULL);
	i = 0;
	while (i < WIN_HEIGHT)
	{
		data->textures->pixel[i] = ft_calloc(WIN_WIDTH + 1,
				sizeof * data->textures->pixel);
		if (!data->textures->pixel[i])
			print_error("data", NULL);
		i++;
	}
}
