/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_put_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciama2 <luciama2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:05:13 by luciama2          #+#    #+#             */
/*   Updated: 2025/03/07 20:05:14 by luciama2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// util function, to add to libft
char	*ft_concat(char *first, ...)
{
	va_list	vargs;
	char	*current;
	char	*tmp;
	char	*rslt;

	va_start(vargs, first);
	rslt = ft_strdup(first);
	if (!rslt)
		return (NULL);
	current = va_arg(vargs, char *);
	while (current)
	{
		tmp = ft_strdup(rslt);
		if (!tmp)
			return (free(rslt), NULL);
		free(rslt);
		rslt = ft_strjoin(tmp, current);
		if (!rslt)
			return (free(tmp), NULL);
		free(tmp);
		current = va_arg(vargs, char *);
	}
	va_end(vargs);
	return (rslt);
}

static char	*get_player_pos_str(t_player *player)
{
	char	*x;
	char	*y;
	char	*rslt;

	x = ft_itoa(player->map_row);
	if (!x)
		return (NULL);
	y = ft_itoa(player->map_col);
	if (!y)
		return (free(x), NULL);
	rslt = ft_concat("PLAYER AT: [", x, ",", y, "]", NULL);
	free(x);
	free(y);
	if (!rslt)
		return (NULL);
	return (rslt);
}

static char	*get_player_dir_str(t_player *player)
{
	char	*x;
	char	*y;
	char	*rslt;

	x = ft_itoa(roundl(cos(player->angle)));
	if (!x)
		return (NULL);
	y = ft_itoa(roundf(sin(player->angle)));
	if (!y)
		return (free(x), NULL);
	rslt = ft_concat("VECTOR: [", x, ",", y, "]", NULL);
	free(x);
	free(y);
	if (!rslt)
		return (NULL);
	return (rslt);
}

void	minimap_put_str(t_cub *cub)
{
	const int	start_x = cub->minimap->start_x;
	char		*str_position;
	char		*str_vector;

	str_position = get_player_pos_str(cub->map->player);
	if (!str_position)
		return ;
	str_vector = get_player_dir_str(cub->map->player);
	if (!str_vector)
	{
		free(str_position);
		return ;
	}
	mlx_string_put(cub->mlx->mlx_ptr, cub->mlx->win, 0, start_x
		+ 16, 0xFF1100, (char *)str_position);
	mlx_string_put(cub->mlx->mlx_ptr, cub->mlx->win, 0, start_x
		+ 32, 0xFF1100, (char *)str_vector);
	free(str_position);
	free(str_vector);
}
