
#include "../includes/cub3d.h"

static void	mov_plus(t_cub *data, char **res, int x, int y)
{
	int i;
	int	j;
	
	i = 0;
	while (res[i])
	{
		j = 0;
		while (res[i][j])
		{
			if (res[i][j] == 'N' || res[i][j] == 'S' ||res[i][j] == 'W' || res[i][j] == 'W')
			{
				if (res[i + x][j + y] != '1')
				{
					res[i][j] = '0';
					i += x;
					j += y;
					data->map->player->x = i;
					data->map->player->y = j;
					res[i][j] = 'N';
				}
			}
			j++;
		}
		i++;
	}
}

void move(t_cub *data, int x, int y)
{
	printf("se esta moviendo.\n");
	char	**res;
	res = data->map->map;
	mov_plus(data, res, x, y);
	data->map->map = res;
}

char	*read_map(char *s)
{
	int		fd;
	char	*res;
	int		count;
	char	buffer[101];

	res = "\n";
	fd = open(s, O_RDONLY);
	if (fd < 0)
		return (NULL);
	count = read(fd, buffer, 100);
	while (count != 0)
	{
		if (count == -1)
			return (NULL);
		buffer[count] = '\0';
		res = ft_strjoin(res, buffer); //TODO hablar con lucia para ver la funcion que libera la memoria
		count = read(fd, buffer, 100);
	}
	return (close(fd), res);
}

void positionPlayer(t_cub *data)
{
	int		i;
	int		j;
	char	**res;

	i = 0;
	res = data->map->map;
	while (res[i])
	{
		j = 0;
		while (res[i][j])
		{
			if (res[i][j] == 'P')
			{
				data->map->player->x = i;
				data->map->player->y = j;
			}
			j++;
		}
		i++;
	}
	
}

