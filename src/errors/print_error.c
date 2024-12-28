#include "../includes/cub3d.h"

int	print_error(char *origin, char *custom_msg)
{	
	printf(RED"Error\n");
	if (DEBUG == 1)
		printf(RED"%s - "RESET, origin);
	if (custom_msg)
		printf(RED"%s (errno: %d)\n"RESET, custom_msg, errno);
	else
		printf(RED"%s (errno %d)\n"RESET, strerror(errno), errno);
	return (-1);
}
