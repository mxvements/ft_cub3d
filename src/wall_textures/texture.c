/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciama2 <luciama2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:06:10 by luciama2          #+#    #+#             */
/*   Updated: 2025/03/07 20:06:11 by luciama2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	init_img(t_cub *data, t_image *image, int width, int height)
{
	ft_memset(image, 0, sizeof(t_image));
	image->img = mlx_new_image(data->mlx->mlx_ptr, width, height);
	if (image->img == NULL)
		return (print_error("new image", NULL));
	image->addr = (int *)mlx_get_data_addr(image->img, &image->pixel_bits,
			&image->size_line, &image->endian);
	return (0);
}
