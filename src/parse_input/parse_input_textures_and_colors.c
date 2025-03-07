/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input_textures_and_colors.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciama2 <luciama2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:05:35 by luciama2          #+#    #+#             */
/*   Updated: 2025/03/07 20:05:36 by luciama2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static char	*get_err_msg(int i)
{
	const char	*err_msg[WALL_SIDES + 2] = {ERR_TXT_NORTH, ERR_TXT_SOUTH, \
			ERR_TXT_WEST, ERR_TXT_EAST, ERR_COL_F, ERR_COL_C};

	if (i >= (WALL_SIDES + 2))
		return (NULL);
	return ((char *)err_msg[i]);
}

static int	save_texture(int j, char *line, t_texture *tx)
{
	char	*filename;
	char	*prefix;
	char	*err_msg;

	err_msg = get_err_msg(j);
	prefix = get_prefix(j);
	if (ft_strncmp(prefix, line, 2) != 0)
		return (0);
	if (is_file_extension(line, ".xpm") < 0)
		return (print_error("save_texture", err_msg));
	filename = ft_strtrim(line + 2, "\t ");
	if (!filename)
		return (print_error("save_texture", NULL));
	if (tx->wall[j])
	{
		free(filename);
		return (print_error("save_texture", ERR_TXT_DUPL));
	}
	tx->wall[j] = filename;
	return (0);
}

static int	save_color(int j, char *line, t_texture *tx)
{
	char		*prefix;
	char		*err_msg;
	char		**rgb;
	long long	color;

	err_msg = get_err_msg(j);
	prefix = get_prefix(j);
	if (ft_strncmp(prefix, line, 1) != 0)
		return (0);
	rgb = ft_split(line + 1, ',');
	if (!rgb)
		return (print_error("save_color", NULL));
	if (is_color(rgb) < 0)
		return (strarr_freenull(&rgb), print_error("save_color", err_msg));
	color = color_str_to_long(rgb);
	strarr_freenull(&rgb);
	if (j == 4)
		tx->floor = color;
	else if (j == 5)
		tx->ceiling = color;
	return (0);
}

static int	check_texture_eof(t_texture *tx)
{
	int	i;

	i = -1;
	while (++i < WALL_SIDES)
	{
		if (tx->wall[i] == NULL || *tx->wall[i] == '\0')
			return (print_error("check_texture_eof", ERR_TXT_MISSING));
	}
	if (tx->ceiling == -1 || tx->floor == -1)
		return (print_error("check_texture_eof", ERR_COL_MISSING));
	return (0);
}

int	parse_texture_and_colors(t_texture *tx, int fd)
{
	char	*line;
	int		i;

	while (1)
	{
		if (is_texture_struct_full(tx) == 1)
			break ;
		line = strtrim_gnl(fd, "\t\n ");
		if (!line)
			return (check_texture_eof(tx));
		if (line && (*line == '0' || *line == '1'))
			return (free(line), check_texture_eof(tx));
		i = -1;
		while (++i < WALL_SIDES + 2 && *line != '\0')
		{
			if (i < WALL_SIDES && save_texture(i, line, tx) < 0)
				return (free(line), line = NULL, -1);
			else if (i >= WALL_SIDES && save_color(i, line, tx) < 0)
				return (free(line), line = NULL, -1);
		}
		free(line);
	}
	return (0);
}
