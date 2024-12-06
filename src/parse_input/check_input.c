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




static int	check_map_by_char_pos(int k, int j, int i, char **map)
{
	const int	dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

	// frst char
	if (k != 3 && j == 0 && map[i + dir[k][0]][j + dir[k][1]] == '0')
		return (print_error(ERR_MAP_SPC));
	// lst char
	else if (k != 2 && j == (int)ft_strlen(map[i]) && map[i + dir[k][0]][j
		+ dir[k][1]] == '0')
		return (print_error(ERR_MAP_SPC));
	// any other char
	else if (map[i + dir[k][0]][j + dir[k][1]] == '0')
		return (print_error(ERR_MAP_SPC));
	return (0);
}

/**
 * PrimeraFila no aplica el		2
 * UltimaFila no aplica el		0
 * PrimeraLetra no apliica el	3
 * Ultima letra no aplica el	1
 *
 * 1aF->  0, 1, 3		1aF 1aL -> 0, 1			1af ultL -> 0, 3
 * cqF->  0, 1, 2, 3	cqF 1aL->  0, 1, 2		cqF ultL -> 0, 2, 3
 * ultF-> 1, 2, 3		ultF 1aL -> 1, 2		ultF ultL -> 2, 3
 *
 * 2	2,3		2,1
 * -	3		1
 * 0	0,3		0,1
 */
int	check_map(char **map)
{
	int			i;
	int			j;
	int			k;
	const int	map_len = strarr_len(map) - 1;
	// const int	dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			// printf("current idx: \'%c\'\n", map[i][j]);
			// first line and last lines check -> cannot have '0'
			if (i == 0 || i == map_len)
			{
				if (map[i][j] == '0')
					return (print_error(ERR_MAP_BOUNDS));
				if (map[i][j] != ' ' && map[i][j] != '1' && map[i][j] != '\n')
				{
					printf("Error on idx [%d, %d], char: \'%c\'\n", i, j,
						map[i][j]);
					return (print_error(ERR_MAP_CHAR));
				}
			}
			// if its a SPACE
			if (map[i][j] == ' ')
			{
				k = 4;
				while (--k >= 0)
				{
					if (i == 0 && k != 2) // first line
					{
						// // frst char
						// if (k != 3 && j == 0 && map[i + dir[k][0]][j
						// 	+ dir[k][1]] == '0')
						// 	return (print_error(ERR_MAP_SPC));
						// // lst char
						// else if (k != 2 && j == (int)ft_strlen(map[i]) && map[i
						// 	+ dir[k][0]][j + dir[k][1]] == '0')
						// 	return (print_error(ERR_MAP_SPC));
						// // any other char
						// else if (map[i + dir[k][0]][j + dir[k][1]] == '0')
						// 	return (print_error(ERR_MAP_SPC));
						check_map_by_char_pos(k, j, i, map);
					}
					else if (i == map_len && k != 0) // last line
					{
						// // frst char
						// if (k != 3 && j == 0 && map[i + dir[k][0]][j
						// 	+ dir[k][1]] == '0')
						// 	return (print_error(ERR_MAP_SPC));
						// // lst char
						// else if (k != 2 && j == (int)ft_strlen(map[i]) && map[i
						// 	+ dir[k][0]][j + dir[k][1]] == '0')
						// 	return (print_error(ERR_MAP_SPC));
						// // any other char
						// else if (map[i + dir[k][0]][j + dir[k][1]] == '0')
						// 	return (print_error(ERR_MAP_SPC));
						check_map_by_char_pos(k, j, i, map);
					}
					else
					{
						check_map_by_char_pos(k, j, i, map);
					}
					// if (map[i + dir[k][0]][j + dir[k][1]])
				}
			}
		}
	}
	return (0);
}
