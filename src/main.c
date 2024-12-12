#include "includes/cub3d.h"

static int	init_map(t_map *map)
{
	map->player = (t_player *)ft_calloc(1, sizeof(t_player));
	if (!map->player)
		return (print_error(NULL)); 
	return (0);
}

static int init_cub(t_cub *cub, char *filepath)
{

	cub->map = (t_map *)ft_calloc(1, sizeof(t_map));
	if (!cub->map)
		return (print_error(NULL));
	if (init_map(cub->map) < 0)
		return (-1);
	cub->textures = (t_texture *)ft_calloc(1, sizeof(t_texture));
	if (!cub->textures)
	{
		free_cub(cub);
		return (print_error(NULL));
	}
	if (parse_input(cub, filepath) < 0)
	{
		free_cub(cub);
		return (-1);
	}
	print_cub(cub);
	return (0);
}


/**
 * CUB3D
 * 
 * Execution
 * 		./cub3d <path/to/map.cub>
 */
int main(int argc, char **argv)
{
	t_cub	cub;

	if (argc != 2)
		print_error(ERR_USE);
	if (check_file_extension(argv[1], ".cub") < 0)
		print_error(ERR_CUB);
	ft_memset(&cub, 0, sizeof(t_cub));
	if (init_cub(&cub, argv[1]) < 0)
		return (1);
	//edu deberia continuar su codigo aqui
	return (0);
}
