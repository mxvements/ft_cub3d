#include "../includes/cub3d.h"

char	*strtrim_gnl(int fd, char *trim)
{
	char	*gnl;
	char	*line;

	gnl = get_next_line(fd);
	if (!gnl)
	{
		return (NULL);
	}
	if (!trim)
		return (gnl);
	line = ft_strtrim(gnl, trim);
	free(gnl);
	if (!line)
		return (NULL);
	return (line);
}

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
	// printf("color_str_to_long: %lli\n", color);
	return (color);
}

/* TODO */
int	color_long_to_hex(long long color);