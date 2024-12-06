#include "cub3d.h"

void    testprintMap(char **map)
{
    int	i;
	int	j;

	i = 0;
	j = 0;
	while(i<10)
	{
		while(map[i][j])
		{
			write(2, &map[i][j], 1);
			j++;
		}
		write(2, "\n", 1);
		j = 0;
		i++;
	}
}