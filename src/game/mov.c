
#include "../includes/cub3d.h"

static void	mov_plus(t_cub *data, char **map, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E'
				|| map[i][j] == 'W')
			{
				if (map[i + x][j + y] != '1')
				{
					map[i][j] = '0';
					i += x;
					j += y;
					data->map->player->x = i;
					data->map->player->y = j;
					map[i][j] = 'N';
				}
			}
			j++;
		}
		i++;
	}
}
/*
	void move_player(t_player *player)
{
	int		speed;
	float	angle_speed;
	float	cos_angle;
	float	sin_angle;

	speed = 5;
	angle_speed = PI/16;
	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	if (player->left_rotate)
		player->angle -= angle_speed;
	if (player->right_rotate)
		player->angle += angle_speed;
	if (player->angle > 2 * PI)
		player->angle = 0;
	if (player->angle > 2*PI)
		player->angle = 2 * PI;
	if (player->key_up)
	{
		player->x -= speed * cos_angle;
		player->y -= speed * sin_angle;
	}
	if (player->key_down)
	{
		player->x += speed * cos_angle;
		player->y += speed * sin_angle;
	}
	if (player->key_left)
	{
		player->x += speed * cos(player->angle + PI / 2);
		player->y += speed * sin(player->angle + PI / 2);
	}
	if (player->key_right)
	{
		player->x -= speed * cos(player->angle + PI / 2);
		player->y -= speed * sin(player->angle + PI / 2);
	}
}
*/



void	move(t_cub *data, int x, int y)
{
	char	**map;

	printf(ORANGE "se esta moviendo.\n" RESET);
	map = data->map->map;
	mov_plus(data, map, x, y);
	data->map->map = map;
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
		res = ft_strjoin(res, buffer);
			// TODO hablar con lucia para ver la funcion que libera la memoria
		count = read(fd, buffer, 100);
	}
	return (close(fd), res);
}

void	positionPlayer(t_cub *data)
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
