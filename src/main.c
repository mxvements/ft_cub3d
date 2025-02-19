#include "includes/cub3d.h"

static int	init_map_struct(t_map *map)
{
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
	tx->floor = -1;
	tx->ceiling = -1;
}

static int	init_cub_struct(t_cub *cub)
{
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
	cub->options.show_minimap = 0;
	cub->options.wall_col = 0;
	cub->options.move_speed = (float)0.1;
	cub->options.rotate_speed = (float)PI / 32; // dividir o multiplicar por 4
	cub->options.fov = (float)PI/6;
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
	// add images after initializing mlx
	if (minimap_set_img(&cub) < 0)
		return (free_cub(&cub), -1);
	if (init_textures(&cub) < 0) //nuevo
		return (free_cub(&cub));
	// start engine
	init_engine(&cub);
	// end
	free_cub(&cub);
	return (0);
}

/**
 * CUB3D
 *
 * Execution
 * 		./cub3d <path/to/map.cub>
 */
int	main(int argc, char **argv)
{
	if (argc != 2)
		print_error("main", ERR_USE);
	// parsing test multiple maps
	if (ft_strncmp(argv[1], "test\0", 5) == 0)
		return (parse_test());
	if (init_cub_game(argv[1]) < 0)
		return (1);
	return (0);
}
