#include "../includes/cub3d.h"

int	test_colors(void)
{
	int			i;
	const char	*files[6] = {
		"./scenes/bad/color_invalid_rgb.cub",
		"./scenes/bad/color_missing_ceiling_rgb.cub",
		"./scenes/bad/color_missing_floor_rgb.cub",
		"./scenes/bad/color_missing.cub",
		"./scenes/bad/color_none.cub",
		NULL
	};

	i = -1;
	printf(ROSE"++++++++++++++++++++ bad colors ++++++++++++++++++++\n"RESET);
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

int	test_textures(void)
{
	int			i;
	const char	*files[7] = {
		"./scenes/bad/textures_dir.cub",
		"./scenes/bad/textures_duplicates.cub",
		"./scenes/bad/textures_invalid.cub",
		"./scenes/bad/textures_missing.cub",
		"./scenes/bad/textures_none.cub",
		"./scenes/bad/textures_not_xpm.cub",
		NULL
	};

	i = -1;
	printf(ROSE"++++++++++++++++++++ bad textures ++++++++++++++++++++\n"RESET);
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
