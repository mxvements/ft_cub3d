#include "../includes/cub3d.h"

// static int text_walls(void)
// {
// 		char *fp26 = "./scenes/bad/wall_hole_east.cub";
// 	char *fp27 = "./scenes/bad/wall_hole_north.cub";
// 	char *fp28 = "./scenes/bad/wall_hole_south.cub";
// 	char *fp29 = "./scenes/bad/wall_hole_west.cub";
// 	char *fp30 = "./scenes/bad/wall_none.cub";
// }



// static int test_player(void)
// {
// 	char *fp16 = "./scenes/bad/player_multiple.cub";
// 	char *fp17 = "./scenes/bad/player_none.cub";
// 	char *fp18 = "./scenes/bad/player_on_edge.cub";
// }

// static int test_map(void)
// {
// 	char *fp11 = "./scenes/bad/map_first.cub";
// 	char *fp12 = "./scenes/bad/map_middle.cub";
// 	char *fp13 = "./scenes/bad/map_missing.cub";
// 	char *fp14 = "./scenes/bad/map_only.cub";
// 	char *fp15 = "./scenes/bad/map_too_small.cub";
// }

// static int test_file(void)
// {
// 	char *fp06 = "./scenes/bad/empty.cub";
// 	char *fp07 = "./scenes/bad/file_letter_end.cub";
// 	char *fp08 = "./scenes/bad/filetype_missing";
// 	char *fp09 = "./scenes/bad/filetype_wrong.buc";
// 	char *fp10 = "./scenes/bad/forbidden.cub";
// }

static int test_colors(void)
{
	int			i;
	const char  *files[5] = {
		"./scenes/bad/color_invalid_rgb.cub",
		"./scenes/bad/color_missing_ceiling_rgb.cub",
		"./scenes/bad/color_missing_floor_rgb.cub",
		"./scenes/bad/color_missing.cub",
		"./scenes/bad/color_none.cub"
	} ;

	i = -1;
	printf(ROSE"++++++++++++++++++++ bad colors ++++++++++++++++++++\n"RESET);
	while (++i < 5)
	{
		if (init_cub_game((char *)files[i]) < 0)
		{
			printf("%s - ", files[i]);
			printf(GREEN"OK\n"RESET);
		}
	}
	return (0);
}

static int test_textures(void)
{
	int			i;
	const char *files[6] = {
		"./scenes/bad/textures_dir.cub",
		"./scenes/bad/textures_duplicates.cub",
		"./scenes/bad/textures_invalid.cub",
		"./scenes/bad/textures_missing.cub",
		"./scenes/bad/textures_none.cub",
		"./scenes/bad/textures_not_xpm.cub"
	} ;
	i = -1;
	printf(ROSE"++++++++++++++++++++ bad textures ++++++++++++++++++++\n"RESET);
	while (++i < 7)
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
	test_colors();
	test_textures();

	
	return (0);
}
