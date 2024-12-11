#include "../includes/cub3d.h"

long long	color_str_to_long(char **rgb)
{
	long long	color;
	int		c;
	int		i;

	color = 0;
	c = 3;
	i = -1;
	while (rgb[++i] && --c >= 0)
		color += ft_atoi(rgb[i]) << (8 * c);
	printf("color: %lld\n", color);
	return (color);
}

/* TODO */
int	color_long_to_hex(long long color);