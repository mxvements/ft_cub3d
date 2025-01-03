
#include "includes/cub3d.h"


static int	close_win(t_cub *data)
{
	mlx_destroy_window(data->mlx->mlx_ptr, data->mlx->win);
	printf("FINISH GAME\n");
	free_cub(data);
	exit(1);
}

static int	ft_hook_key(int key, t_cub *cub)
{
	
	if (key == KEY_ESC)
		close_win(cub);
	if (key == KEY_A || key == KEY_LEFT)
	{
		move(cub, 0, -1);
		render_map(cub, cub->map);

		// double oldDirX = dirX;
		// dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
		// dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
		// double oldPlaneX = planeX;
		// planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
		// planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
	}
	if (key == KEY_S || key == KEY_DOWN)
	{
		move(cub, 1, 0);
		render_map(cub, cub->map);

		// if(worldMap[int(posX - dirX * moveSpeed)][int(posY)] == false) posX -= dirX * moveSpeed;
    	// if(worldMap[int(posX)][int(posY - dirY * moveSpeed)] == false) posY -= dirY * moveSpeed;
	}
	if (key == KEY_D || key == KEY_RIGHT)
	{
		move(cub, 0, 1);
		render_map(cub, cub->map);

		// double oldDirX = dirX;
		// dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
		// dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
		// double oldPlaneX = planeX;
		// planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
		// planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
	}
	if (key == KEY_W || key == KEY_UP)
	{
		move(cub, -1, 0);
		render_map(cub, cub->map);

		// if(worldMap[int(posX + dirX * moveSpeed)][int(posY)] == false) posX += dirX * moveSpeed;
      	// if(worldMap[int(posX)][int(posY + dirY * moveSpeed)] == false) posY += dirY * moveSpeed;
	}
	// ray(cub);
	/* printf("jugador x->%f, y->%f\n", data->player->x, data->player->y); */
	return (0);
}

int init_mlx(t_cub *cub)
{
	t_mlx	*mlx;

	cub->mlx = ft_calloc(1, sizeof(t_mlx));
	if (!cub->mlx)
		return (print_error("init_mlx", NULL));
	mlx = cub->mlx;
	mlx->mlx_ptr = mlx_init();
	// printf("x-> %d y y-> %d.\n",data->x_max, data->y_max );
	mlx->win = mlx_new_window(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "main-window");
	add_minimap(cub);
	// render_map(cub, cub->map);
	mlx_key_hook(mlx->win, ft_hook_key, cub);
	mlx_hook(mlx->win, 17, 0, close_win, cub);
	mlx_loop(mlx->mlx_ptr);
	return (0);
}
