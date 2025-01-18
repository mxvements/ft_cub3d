#include "../includes/cub3d.h"

//imprime las primeras 10 rows del mapa
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

void	set_image_pixel(t_img *image, int x, int y, int color)
{
	int	pixel;

	pixel = y * (image->size_line / 4) + x;
	image->addr[pixel] = color;
}