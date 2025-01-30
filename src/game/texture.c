
#include "../includes/cub3d.h"


static void	init_img_clean(t_imgen *img)
{
	img->img = NULL;
	img->addr = NULL;
	img->pixel_bits = 0;
	img->size_line = 0;
	img->endian = 0;
}


static void	init_texture_img(t_cub *data, t_imgen *image, char *path)
{
	int	width;
	int	height;

	init_img_clean(image);
	image->img = mlx_xpm_file_to_image(data->mlx->mlx_ptr, path, &width,
			&height);
	if (image->img == NULL)
		print_error('callo', NULL);
	image->addr = (int *)mlx_get_data_addr(image->img, &image->pixel_bits,
			&image->size_line, &image->endian);
	return ;
}

static int	*xpm_to_img(t_cub *data, char *path)
{
	t_imgen	tmp;
	int		*buffer;
	int		x;
	int		y;

	init_texture_img(data, &tmp, path);
	// printf("tamaño -> %d\n", sizeof * buffer * PIXEL_SIZE * PIXEL_SIZE);
	buffer = ft_calloc(1,
			sizeof * buffer * PIXEL_SIZE * PIXEL_SIZE);
	if (!buffer)
		print_error('callo', NULL);
	y = 0;
	while (y < PIXEL_SIZE)
	{
		x = 0;
		while (x < PIXEL_SIZE)
		{
			buffer[y * PIXEL_SIZE + x]
				= tmp.addr[y * PIXEL_SIZE + x];
			++x;
		}
		y++;
	}
	mlx_destroy_image(data->mlx->mlx_ptr, tmp.img);
	return (buffer);
}

void	init_img(t_cub *data, t_imgen *image, int width, int height)
{
	init_img_clean(image);
	image->img = mlx_new_image(data->mlx->mlx_ptr, width, height);
	if (image->img == NULL)
		print_error('new image', NULL);
	image->addr = (int *)mlx_get_data_addr(image->img, &image->pixel_bits,
			&image->size_line, &image->endian);
	return ;
}

void	init_textures(t_cub *data)
{
	data->textures->text = ft_calloc(5, sizeof * data->textures);
	if (!data->textures->text)
		print_error('callo', NULL);
	data->textures->text[NORTH] = xpm_to_img(data, data->textures->wall[NORTH]);
	data->textures->text[SOUTH] = xpm_to_img(data, data->textures->wall[SOUTH]);
	data->textures->text[EAST] = xpm_to_img(data, data->textures->wall[EAST]);
	data->textures->text[WEST] = xpm_to_img(data, data->textures->wall[WEST]);
}
/* void	init_texture_pixels(t_cub *data)
{
	int	i;

	if (data->texture_pixels)
		free_tab((void **)data->texture_pixels);
	data->texture_pixels = ft_calloc(data->win_height + 1,
			sizeof * data->texture_pixels);
	if (!data->texture_pixels)
		clean_exit(data, err_msg(NULL, ERR_MALLOC, 1));
	i = 0;
	while (i < data->win_height)
	{
		data->texture_pixels[i] = ft_calloc(data->win_width + 1,
				sizeof * data->texture_pixels);
		if (!data->texture_pixels[i])
			clean_exit(data, err_msg(NULL, ERR_MALLOC, 1));
		i++;
	}
} */

/* static void	get_texture_index(t_data *data, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->dir_x < 0)
			data->texinfo.index = WEST;
		else
			data->texinfo.index = EAST;
	}
	else
	{
		if (ray->dir_y > 0)
			data->texinfo.index = SOUTH;
		else
			data->texinfo.index = NORTH;
	}
} */

/* void	update_texture_pixels(t_data *data, t_texinfo *tex, t_ray *ray, int x)
{
	int			y;
	int			color;

	get_texture_index(data, ray);
	tex->x = (int)(ray->wall_x * tex->size);
	if ((ray->side == 0 && ray->dir_x < 0)
		|| (ray->side == 1 && ray->dir_y > 0))
		tex->x = tex->size - tex->x - 1;
	tex->step = 1.0 * tex->size / ray->line_height;
	tex->pos = (ray->draw_start - data->win_height / 2
			+ ray->line_height / 2) * tex->step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex->y = (int)tex->pos & (tex->size - 1);
		tex->pos += tex->step;
		color = data->textures[tex->index][tex->size * tex->y + tex->x];
		if (tex->index == NORTH || tex->index == EAST)
			color = (color >> 1) & 8355711;
		if (color > 0)
			data->texture_pixels[y][x] = color;
		y++;
	}
} */
