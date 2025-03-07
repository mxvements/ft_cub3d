#include "../includes/cub3d.h"

int	is_file_extension(char *filepath, char *extension)
{
	const int	ext_len = ft_strlen(extension);
	const int	path_len = ft_strlen(filepath);
	const int	start = path_len - ext_len;
	int			i;

	i = 0;
	while (filepath[start + i])
	{
		if (filepath[start + i] - extension[i] != 0)
			return (-1);
		i++;
	}
	return (0);
}

int	is_color(char **rgb)
{
	const int	arr_len = 3;
	int			i;
	int			tmp_col;

	if (!rgb || strarr_len(rgb) != arr_len)
		return (-1);
	i = -1;
	while (++i < arr_len && rgb[i])
	{
		tmp_col = ft_atoi(rgb[i]);
		if (tmp_col < 0 || tmp_col > 255)
			return (-1);
	}
	return (0);
}

int	is_texture_struct_full(t_texture *tx)
{
	int	i;

	i = -1;
	while (++i < WALL_SIDES)
	{
		if (tx->wall[i] == NULL || *tx->wall[i] == '\0')
			return (0);
	}
	if (tx->ceiling == -1 || tx->floor == -1)
		return (0);
	return (1);
}

int	is_player(t_player *player)
{
	if (player->map_row == -1 || player->map_col == -1)
		return (0);
	return (1);
}

int	is_player_on_edge(t_map *map, t_player *player)
{
	if (player->map_row == 0 || player->map_col == 0 \
		|| player->map_row == map->rows || player->map_col == map->cols)
		return (print_error("is_player", ERR_PL_EDGE));
	return (0);
}
