#include "../includes/cub3d.h"

void print_options_status(t_options *options)
{
	printf(YLLW "\n[options status]\n" RESET);
	printf("wall collisions\t %d\n", options->wall_col);
	printf("show minimap\t %d\n", options->show_minimap);
	printf("move speed\t %f\n", options->move_speed);
	printf("rotate speed\t %f\n", options->rotate_speed);
}

void	print_key_options(t_cub *cub)
{
	(void)cub;
	printf(LGREEN "\n[CUB3D OPTIONS]\n" RESET);
	printf(LGREEN "+ Change options status with the following keys:\n" RESET);
	printf(LGREEN "  +  show options on console\t (o)\n" RESET);
	printf(LGREEN "  +  show status on console\t (space tab)\n" RESET);
	printf(LGREEN "  +  show game info on console\t (i)\n" RESET);
	printf(LGREEN "  +  wall collisions\t\t (F1)\n" RESET);
	printf(LGREEN "  +  show/hide minimap\t\t (F2)\n" RESET);
	printf(LGREEN "  +  move speed\t\t\t (F3/F4 -/+)\n" RESET);
	printf(LGREEN "  +  rotate speed\t\t (F5/F6 -/+)\n" RESET);
	printf("\n");
}
