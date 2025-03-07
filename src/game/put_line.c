/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciama2 <luciama2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:04:49 by luciama2          #+#    #+#             */
/*   Updated: 2025/03/07 20:04:50 by luciama2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
/**
 * @brief Renders a vertical slice of a wall texture onto the window's img.
 *
 * This function calculates texture coordinates for each pixel of the wall 
 * slice and draws the corresponding pixel from the texture onto the screen. 
 * The `offset` and `tex_x`,`tex_y` values determine the exact point on the texture 
 * based on the ray's intersection with the wall and the wall's height.
 *
 * The `offset` is calculated by dividing the horizontal distance where the 
 * ray hits the wall by the total width of the wall’s minimap tile. This 
 * results in a value between [0, 1] that represents the relative position of 
 * the hit point on the tile. The `tex_x` value is then calculated by scaling 
 * the `offset` to the texture width to find the exact x-coordinate of the 
 * texture.
 *
 * It ensures texture coordinates are within bounds, and handles out-of-bounds 
 * access by clipping or using a default color.
 *
 * @param cub The game's context data structure
 * @param row Array int[2] specifying the [start, end] rows for the slice.
 * @param wall_height The height of the wall based on distance.
 * @param i The index of the hit information in `cub->hits`.
 */
static void	texture_wall(t_cub *cub, int row[2], float wall_height, int i)
{
	const int	side = cub->hits[i].texture_idx;
	int			j;
	float		tex_x;
	float		tex_y;
	int			color;
	float		offset;

	offset = (wall_offset(cub, i) / MINIMAP_PX);
	tex_x = (int)round((wall_offset(cub, i) / MINIMAP_PX) * IMG_PX);
	j = row[0];
	while (row[1] > j)
	{
		tex_y = (int)round((j - row[0]) * (IMG_PX / wall_height));
		if (side < 0 || side >= WALL_SIDES || ((tex_y * IMG_PX) + tex_x) < 0)
			color = 0x000000;
		else if (((tex_y * IMG_PX) + tex_x) > IMG_PX * IMG_PX - 1)
			color = cub->textures->text[side][(int)round(IMG_PX * IMG_PX - 1)];
		else
			color = cub->textures->text[side][(int)round((tex_y * IMG_PX) + tex_x)];
		put_pixel(i, j, color, cub);
		j++;
	}
}

static void	put_line(t_cub *cub, int i)
{
	float	wall_height;
	int		row[2];

	// printf("-->%f\n", cub->hits[i].dist);
	if (cub->hits[i].dist < 0.01f)
		wall_height = (WIN_HEIGHT * MINIMAP_PX);
	else
		wall_height = (WIN_HEIGHT * MINIMAP_PX) / cub->hits[i].dist;
	row[0] = ((WIN_HEIGHT - wall_height) / 2);
	row[1] = (row[0] + wall_height);
	texture_ceiling(cub, row[0], i);
	texture_wall(cub, row, wall_height, i);
	texture_floor(cub, row[1], i);
}

/**
 * @brief Renders the 3D perspective view of the world based on the player's 
 * position and orientation.
 *
 * This function calculates the distance to walls and objects for each column 
 * of the screen, simulating a 3D perspective by casting rays from the player's 
 * position and rendering the corresponding vertical slices of the scene. 
 * The field of view (FOV) and the player's angle are taken into account 
 * for correct projection.
 *
 * It iterates over each column of the screen and adjusts the ray's angle to 
 * create the proper perspective, then calls `get_distance` to calculate 
 * distances and `put_line` to render the walls and objects in the correct 
 * perspective.
 *
 * @param cub The game's context data structure.
 */
void	put_perspective(t_cub *cub)
{
	t_player	*player;
	float		fraction;
	float		start_angle;
	int			screen_col_idx;

	player = cub->map->player;
	fraction = (cub->options.fov) / WIN_WIDTH;
	start_angle = player->angle - (cub->options.fov / 2);
	screen_col_idx = WIN_WIDTH;
	while (screen_col_idx > 0)
	{
		get_distance(cub, cos(start_angle), sin(start_angle), screen_col_idx);
		put_line(cub, screen_col_idx);
		start_angle += fraction;
		screen_col_idx--;
	}
}
