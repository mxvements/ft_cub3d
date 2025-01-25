
#include "includes/cub3d.h"

static void	clean_img(t_cub *cub)
{
	int	i;
	int	j;

	i = -1;
	while (++i < WIN_HEIGHT)
	{
		j = -1;
		while (++j < WIN_WIDTH)
			put_pixel(j, i, 0x00, cub);
	}
}

static int	render_loop(t_cub *cub)
{
	t_mlx	*mlx;

	mlx = cub->mlx;
	// move settings? to recalculate after key_press
	clean_img(cub);
	move_and_rotate(cub);
	// RENDER/DRAW everything
	// render(cub, cub->map);
	if (cub->options.show_minimap == 1)
		minimap_render(cub);
	put_camera(cub); // puts rays in minimap and draws perspective
	if (cub->options.show_minimap == 1)
	{
		minimap_put_player(cub, 0xFF0000);
		minimap_put_axis(cub, 0xFF0000);
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, mlx->img, 0, 0);
	if (cub->options.show_minimap == 1)
		minimap_put_str(cub);
	// RAYCASTING
	// ray(cub);
	return (0);
}

int	init_engine(t_cub *cub)
{
	t_mlx	*mlx;

	mlx = cub->mlx;
	printf(LGREEN"\n****************\n");
	printf("*  START GAME  *\n");
	printf("****************\n"RESET);
	print_key_options(cub);
	mlx_hook(mlx->win, 2, 1L << 0, key_press, cub);
	mlx_hook(mlx->win, 3, 1L << 1, key_release, cub);
	mlx_hook(mlx->win, 17, 0, win_close, cub);
	mlx_loop_hook(mlx->mlx_ptr, render_loop, cub);
	mlx_loop(mlx->mlx_ptr);
	return (0);
}

int	init_mlx(t_cub *cub)
{
	t_mlx	*mlx;

	cub->mlx = ft_calloc(1, sizeof(t_mlx));
	if (!cub->mlx)
		return (print_error("init_mlx", NULL));
	mlx = cub->mlx;
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
		return (print_error("init-mlx", NULL));
	// printf("x-> %d y y-> %d.\n",data->x_max, data->y_max );
	mlx->win = mlx_new_window(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	if (!mlx->win)
		return (print_error("init-mlx", NULL));
	mlx->img = mlx_new_image(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (!mlx->img)
		return (print_error("init-mlx", NULL));
	mlx->img_addr = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->line_len,
			&mlx->endian);
	if (!mlx->img_addr)
		return (print_error("init-mlx", NULL));
	return (0);
}
