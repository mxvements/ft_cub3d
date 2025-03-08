/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlu <zlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:04:20 by luciama2          #+#    #+#             */
/*   Updated: 2025/03/08 11:42:20 by zlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	put_pixel(int col, int row, int color, t_cub *cub)
{
	int	index;

	if (!cub || !cub->mlx)
		return ;
	if (col >= WIN_WIDTH || row >= WIN_HEIGHT || row < 0 || col < 0)
		return ;
	index = (row * cub->mlx->line_len) + (col * cub->mlx->bpp / 8);
	cub->mlx->img_addr[index] = color & 0xFF;
	cub->mlx->img_addr[index + 1] = (color >> 8) & 0xFF;
	cub->mlx->img_addr[index + 2] = (color >> 16) & 0xFF;
}
