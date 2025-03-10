/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlu <zlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:06:16 by luciama2          #+#    #+#             */
/*   Updated: 2025/03/08 11:23:44 by zlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

static int	init_map_struct(t_map *map)
{
	if (!map)
		return (0);
	map->player = (t_player *)ft_calloc(1, sizeof(t_player));
	if (!map->player)
		return (print_error("init_map", NULL));
	map->player->map_row = -1;
	map->player->map_col = -1;
	map->player->win_row = -1;
	map->player->win_col = -1;
	return (0);
}

static void	init_texture_struct(t_texture *tx)
{
	int	i;

	if (!tx)
		return ;
	ft_memset(tx, 0, sizeof(t_texture));
	tx->floor = -1;
	tx->ceiling = -1;
	i = -1;
	while (++i < WALL_SIDES)
	{
		tx->wall[i] = NULL;
		tx->text[i] = NULL;
	}
	tx->pixel = NULL;
}

static int	init_cub_struct(t_cub *cub)
{
	if (!cub)
		return (0);
	cub->map = (t_map *)ft_calloc(1, sizeof(t_map));
	if (!cub->map)
		return (print_error("init_cub", NULL));
	if (init_map_struct(cub->map) < 0)
		return (-1);
	cub->textures = (t_texture *)ft_calloc(1, sizeof(t_texture));
	if (!cub->textures)
	{
		free_cub(cub);
		return (print_error("init_cub", NULL));
	}
	init_texture_struct(cub->textures);
	return (0);
}

static void	init_options(t_cub *cub)
{
	if (!cub)
		return ;
	cub->options.show_minimap = 0;
	cub->options.wall_col = 0;
	cub->options.move_speed = (float)0.2;
	cub->options.rotate_speed = (float)PI / 32;
	cub->options.fov = (float)PI / 4;
}

int	init_cub_game(char *filepath)
{
	t_cub	cub;

	if (is_file_extension(filepath, ".cub") < 0)
		return (print_error("main", ERR_CUB));
	ft_memset(&cub, 0, sizeof(t_cub));
	init_options(&cub);
	if (init_cub_struct(&cub) < 0)
		return (-1);
	if (parse_input(&cub, filepath) < 0)
		return (free_cub(&cub), -1);
	if (minimap_init(&cub) < 0)
		return (free_cub(&cub), -1);
	if (init_mlx(&cub) < 0)
		return (free_cub(&cub), -1);
	if (init_textures(&cub) < 0)
		return (free_cub(&cub));
	init_engine(&cub);
	free_cub(&cub);
	return (0);
}
