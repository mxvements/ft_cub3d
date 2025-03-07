/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_square.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciama2 <luciama2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:04:23 by luciama2          #+#    #+#             */
/*   Updated: 2025/03/07 20:04:24 by luciama2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	put_square(int prow, int pcol, int color, t_cub *cub)
{
	int	row;
	int	col;
	int	size = MINIMAP_PX / 2;

	row = -1;
	while (++row < size)
	{
		col = -1;
		while (++col < size)
			put_pixel(prow + row, pcol + col, color, cub);
	}
}


