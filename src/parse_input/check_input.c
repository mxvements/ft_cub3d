#include "../includes/cub3d.h"

int	check_file_extension(char *filepath, char *extension)
{
	const int	ext_len = ft_strlen(extension);
	const int	path_len = ft_strlen(filepath);
	const int	start = path_len - ext_len;
	int			i;

	i = 0;
	// printf("%s\n", filepath + start);
	while (filepath[start + i])
	{
		if (filepath[start + i] - extension[i] != 0)
			return (-1);
		i++;
	}
	mlx_init();
	return (0);
}

int	check_color(char **rgb)
{
	if (!rgb || strarr_len(rgb) != 3)
		return (-1);
	return (0);
}