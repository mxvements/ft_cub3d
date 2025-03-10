/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_test_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciama2 <luciama2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:05:46 by luciama2          #+#    #+#             */
/*   Updated: 2025/03/07 20:05:47 by luciama2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	text_walls(void)
{
	int			i;
	const char	*files[6] = {
		"./scenes/bad/wall_hole_east.cub",
		"./scenes/bad/wall_hole_north.cub",
		"./scenes/bad/wall_hole_south.cub",
		"./scenes/bad/wall_hole_west.cub",
		"./scenes/bad/wall_none.cub",
		NULL
	};

	i = -1;
	printf(ROSE"++++++++++++++++++++ bad walls ++++++++++++++++++++\n"RESET);
	while (files[++i])
	{
		if (init_cub_game((char *)files[i]) < 0)
		{
			printf("%s - ", files[i]);
			printf(GREEN"OK\n"RESET);
		}
	}
	return (0);
}

static int	test_player(void)
{
	int			i;
	const char	*files[4] = {
		"./scenes/bad/player_multiple.cub",
		"./scenes/bad/player_none.cub",
		"./scenes/bad/player_on_edge.cub",
		NULL
	};

	i = -1;
	printf(ROSE"++++++++++++++++++++ bad player ++++++++++++++++++++\n"RESET);
	while (files[++i])
	{
		if (init_cub_game((char *)files[i]) < 0)
		{
			printf("%s - ", files[i]);
			printf(GREEN"OK\n"RESET);
		}
	}
	return (0);
}

static int	test_map(void)
{
	int			i;
	const char	*files[6] = {
		"./scenes/bad/map_first.cub",
		"./scenes/bad/map_middle.cub",
		"./scenes/bad/map_missing.cub",
		"./scenes/bad/map_only.cub",
		"./scenes/bad/map_too_small.cub",
		NULL
	};

	i = -1;
	printf(ROSE"++++++++++++++++++++ bad map ++++++++++++++++++++\n"RESET);
	while (files[++i])
	{
		if (init_cub_game((char *)files[i]) < 0)
		{
			printf("%s - ", files[i]);
			printf(GREEN"OK\n"RESET);
		}
	}
	return (0);
}

static int	test_file(void)
{
	int			i;
	const char	*files[5] = {
		"./scenes/bad/empty.cub",
		"./scenes/bad/file_letter_end.cub",
		"./scenes/bad/filetype_missing",
		"./scenes/bad/filetype_wrong.buc",
		NULL
	};

	i = -1;
	printf(ROSE"++++++++++++++++++++ bad file ++++++++++++++++++++\n"RESET);
	while (files[++i])
	{
		if (init_cub_game((char *)files[i]) < 0)
		{
			printf("%s - ", files[i]);
			printf(GREEN"OK\n"RESET);
		}
	}
	return (0);
}

int	parse_test(void)
{
	printf(ROSE"++++++++++++++++++++ TEST! ++++++++++++++++++++\n\n"RESET);
	test_file();
	test_colors();
	test_textures();
	test_map();
	test_player();
	text_walls();
	return (0);
}
