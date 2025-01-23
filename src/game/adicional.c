#include "../includes/cub3d.h"

//imprime las primeras 10 rows del mapa
void    testprintMap(char **map)
{
    int	i;
	int	j;

	i = 0;
	j = 0;
	while(i<10)
	{
		while(map[i][j])
		{
			write(2, &map[i][j], 1);
			j++;
		}
		write(2, "\n", 1);
		j = 0;
		i++;
	}
}

static void	set_image_pixel(t_imgen *image, int x, int y, int color)
{
	int	pixel;

	pixel = y * (image->size_line / 4) + x;
	image->addr[pixel] = color;
}

static void	set_frame_image_pixel(t_cub *data, t_img *image, int x, int y)
{
	if (data->textures->text[y][x] > 0)
		set_image_pixel(image, x, y, data->textures->text[y][x]);
	/* else if (y < WIN_HEIGHT / 2)
		set_image_pixel(image, x, y, data->texinfo.hex_ceiling);
	else if (y < WIN_HEIGHT -1)
		set_image_pixel(image, x, y, data->texinfo.hex_floor); */
}



void	render_frame(t_cub *data)
{
	t_imgen	image;
	int		x;
	int		y;

	image.img = NULL;
	/* init_img(data, &image, WIN_WIDTH, WIN_HEIGHT); */
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
	mlx_put_image_to_window(data->mlx->mlx_ptr, data->mlx->win, image.img, 0, 0);
	mlx_destroy_image(data->mlx->mlx_ptr, image.img);
}