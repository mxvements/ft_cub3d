#include "../includes/cub3d.h"

/**
 * @brief Get the excluded vector by char object.
 * 
 * + Fist char: excludes vector {0, -1} on idx 3, which would go a char before
 * 
 * + Inside char: does not excludes any vector, returns -1
 * 
 * + Last char: excludes vecor {0, 1} on idx 1, which would go a char after
 * 
 * @param map 
 * @param char_idx 
 * @return int 
 */
static int	get_excluded_vector_by_char(t_map *map, int char_idx)
{
	const int	char_exclusion[] = {3, -1, 1};

	if (char_idx == 0)
		return (char_exclusion[0]);
	else if (char_idx == map->cols - 1)
		return (char_exclusion[2]);
	else
		return (char_exclusion[1]);
}


/**
 * @brief Get the excluded vector by line position
 * 
 * - Fist line: excludes vector {-1,0} on idx 2, which would go a row above
 * 
 * - Inside line: does not exclude any vector, we return -1
 * 
 * - Last line: excludes vector {1, 0} on idx 1, which would go a row below
 * 
 * @param map 
 * @param line_idx 
 * @return * int, index position of the vector to exclude
 */
static int	get_excluded_vector_by_line(t_map *map, int line_idx)
{
	const int	line_exclusion[] = {2, -1, 0};

	if (line_idx == 0)
		return (line_exclusion[0]);
	else if (line_idx == map->rows - 1)
		return (line_exclusion[2]);
	else
		return (line_exclusion[1]);
}

static int	check_map_by_vectors(int i, int j, t_map *map)
{
	int			k;
	int			excl_vector_by_line;
	int			excl_vector_by_char;
	const int	vectors[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

	excl_vector_by_line = get_excluded_vector_by_line(map, i);
	excl_vector_by_char = get_excluded_vector_by_char(map, j);
	// printf("k excluded by char: %d\n", excl_v_idx_by_char);
	// printf("k excluded by line: %d\n", excl_v_idx_by_line);
	k = 4;
	while (--k >= 0)
	{
		if (k != excl_vector_by_line && k != excl_vector_by_char)
		{
			if (map->map[i][j] == ' '
				&& map->map[i+ vectors[k][0]][j + vectors[k][1]] == '0')
				return (print_error(ERR_MAP_SPC));
			if (map->map[i][j] == '0'
				&& map->map[i+ vectors[k][0]][j + vectors[k][1]] == ' ')
				return (print_error(ERR_MAP_0));
		}
	}
	return (0);
}

int	check_map(t_map *map)
{
	int	i;
	int	j;

	i = -1;
	while (map->map[++i])
	{
		j = -1;
		while (map->map[i][++j])
		{
			// first line and last lines check -> cannot have '0'
			if (i == 0 || i == map->rows - 1)
			{
				if (map->map[i][j] == '0')
					return (print_error(ERR_MAP_BOUNDS));
			}
			if (check_map_by_vectors(i, j, map) < 0)
				return (-1);
		}
	}
	return (0);
}
