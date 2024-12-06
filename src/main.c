#include "includes/cub3d.h"

static void *init_cub(char *filepath)
{
	t_cub		*cub;

	cub = (t_cub *)ft_calloc(1, sizeof(t_cub));
	if (!cub)
		return (NULL); //print message 
	cub->map = (t_map *)ft_calloc(1, sizeof(t_map));
	if (!cub->map)
		return (NULL); //print message in case of error & free
	cub->textures = (t_texture *) ft_calloc(1, sizeof(t_texture));
	if (!cub->textures)
		return (NULL); //print message in case of error & free
	
	cub = parse_input(cub, filepath);
	if (!cub)
	{
		printf("Should free the map here");
		return (NULL); //print message & free
	}
	return (cub);
}


/**
 * CUB3D
 * 
 * Execution
 * 		./cub3d <path/to/map.cub>
 */
int main(int argc, char **argv)
{
	void *status;

	if (argc != 2)
		print_error(ERR_USE);
	if (check_file_extension(argv[1], ".cub") < 0)
		print_error(ERR_CUB);
	status = init_cub(argv[1]);
	if (!status)
		return (1);
		
	
	return (0);
}