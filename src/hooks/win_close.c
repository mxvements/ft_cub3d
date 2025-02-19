#include "../includes/cub3d.h"

int	win_close(t_cub *cub)
{
	free_cub(cub);
	printf(LGREEN "\n*****************\n");
	printf("*  FINISH GAME  *\n");
	printf("*****************\n" RESET);
	exit(0);
}
