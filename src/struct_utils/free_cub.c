/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciama2 <luciama2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:05:56 by luciama2          #+#    #+#             */
/*   Updated: 2025/03/07 20:05:57 by luciama2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	free_texture(void *data)
{
	t_texture	*texture;

	texture = data;
	if (texture->wall[NORTH])
		ft_freenull(&texture->wall[NORTH]);
	if (texture->wall[SOUTH])
		ft_freenull(&texture->wall[SOUTH]);
	if (texture->wall[EAST])
		ft_freenull(&texture->wall[EAST]);
	if (texture->wall[WEST])
		ft_freenull(&texture->wall[WEST]);
	if (texture->text[NORTH])
		free_int_ptr(&texture->text[NORTH]);
	if (texture->text[SOUTH])
		free_int_ptr(&texture->text[SOUTH]);
	if (texture->text[EAST])
		free_int_ptr(&texture->text[EAST]);
	if (texture->text[WEST])
		free_int_ptr(&texture->text[WEST]);
}

static void	free_minimap(t_mlx *mlx, t_minimap *minimap)
{
	if (minimap->img_wall)
		mlx_destroy_image(mlx->mlx_ptr, minimap->img_wall);
	if (minimap->img_floor)
		mlx_destroy_image(mlx->mlx_ptr, minimap->img_floor);
	if (minimap->img_player)
		mlx_destroy_image(mlx->mlx_ptr, minimap->img_player);
	if (minimap->img_void)
		mlx_destroy_image(mlx->mlx_ptr, minimap->img_void);
}

static void	free_mlx(void *data)
{
	t_mlx	*mlx;

	mlx = data;
	mlx_destroy_image(mlx->mlx_ptr, mlx->img);
	mlx->img = NULL;
	mlx->img_addr = NULL;
	mlx_destroy_window(mlx->mlx_ptr, mlx->win);
	mlx->win = NULL;
	mlx_destroy_display(mlx->mlx_ptr);
	mlx->mlx_ptr = NULL;
}

/* cub is never mallocked, we just need to free the nested structs */
int	free_cub(t_cub *cub)
{
	if (cub->map)
		free_struct((void **)&cub->map, free_map);
	if (cub->textures)
		free_struct((void **)&cub->textures, free_texture);
	if (cub->minimap)
	{
		free_minimap(cub->mlx, cub->minimap);
		free(cub->minimap);
		cub->minimap = NULL;
	}
	if (cub->mlx)
		free_struct((void **)&cub->mlx, free_mlx);
	return (0);
}
