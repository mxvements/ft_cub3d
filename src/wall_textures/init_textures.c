#include "../includes/cub3d.h"

static int	init_texture_img(t_cub *data, t_image *image, char *path)
{
	int	width;
	int	height;

	ft_memset(image, 0, sizeof(t_image));
	image->img = mlx_xpm_file_to_image(data->mlx->mlx_ptr, path, &width,
			&height);
	if (!image->img)
		return (print_error("init_texture_img", NULL));
	image->addr = (int *)mlx_get_data_addr(image->img, &image->pixel_bits,
			&image->size_line, &image->endian);
	return (0);
}

static int	*xpm_to_img(t_cub *data, char *path)
{
	t_image	tmp;
	int		*buffer;
	int		x;
	int		y;

	buffer = ft_calloc(IMG_PX * IMG_PX, sizeof(int));
	if (!buffer)
		return (print_error("xpm_to_img", NULL), NULL);
	if (init_texture_img(data, &tmp, path) < 0)
		return (free(buffer), NULL);
	if (!tmp.addr)
	{
		mlx_destroy_image(data->mlx->mlx_ptr, tmp.img);
		free(buffer);
		return (print_error("xpm_to_img", "Failed to get texture data."), NULL);
	}
	y = -1;
	while (++y < IMG_PX)
	{
		x = -1;
		while (++x < IMG_PX)
			buffer[y * IMG_PX + x] = tmp.addr[y * IMG_PX + x];
	}
	mlx_destroy_image(data->mlx->mlx_ptr, tmp.img);
	return (buffer);
}
int	init_textures(t_cub *cub)
{
	cub->textures->text[NORTH] = xpm_to_img(cub, cub->textures->wall[NORTH]);
	if (!cub->textures->text[NORTH])
		return (-1);
	cub->textures->text[SOUTH] = xpm_to_img(cub, cub->textures->wall[SOUTH]);
	if (!cub->textures->text[SOUTH])
		return (-1);
	cub->textures->text[EAST] = xpm_to_img(cub, cub->textures->wall[EAST]);
	if (!cub->textures->text[EAST])
		return (-1);
	cub->textures->text[WEST] = xpm_to_img(cub, cub->textures->wall[WEST]);
	if (!cub->textures->text[WEST])
		return (-1);
	return (0);
}
