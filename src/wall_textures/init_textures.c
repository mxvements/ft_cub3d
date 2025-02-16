#include "../includes/cub3d.h"

static int	init_texture_img(t_cub *data, t_image *image, char *path)
{
	int	width;
	int	height;

	// clean_img(image);
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

	if (init_texture_img(data, &tmp, path) < 0)
		return (NULL);
	// printf("tamaño -> %d\n", sizeof * buffer * PIXEL_SIZE * PIXEL_SIZE);
	buffer = ft_calloc(PIXEL_SIZE * PIXEL_SIZE, sizeof(int));
	if (!buffer)
		return (print_error("xpm_to_img", NULL), NULL);
	if (!tmp.addr)
	{
		mlx_destroy_image(data->mlx->mlx_ptr, tmp.img);
		return (print_error("xpm_to_img", "Failed to get texture data."), NULL);
	}
	y = -1;
	while (++y < PIXEL_SIZE)
	{
		x = -1;
		while (++x < PIXEL_SIZE)
			buffer[y * PIXEL_SIZE + x] = tmp.addr[y * PIXEL_SIZE + x];
	}
	mlx_destroy_image(data->mlx->mlx_ptr, tmp.img);
	return (buffer);
}

int	init_textures(t_cub *cub)
{
	// cub->textures->text = ft_calloc(5, sizeof *cub->textures);
	cub->textures->text = ft_calloc(5, sizeof(int *));
	if (!cub->textures->text)
		return (print_error("init_texture", NULL));
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
	// printf("init_textures\n");
	return (0);
}
