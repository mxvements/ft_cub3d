#include "../includes/cub3d.h"

void	print_error(char *custom_msg)
{	
	if (custom_msg)
		printf(RED"Error\n%s (errno: %d)\n"RESET, custom_msg, errno);
	else
		printf(RED"Error\n%s (errno %d)\n"RESET, strerror(errno), errno);
}