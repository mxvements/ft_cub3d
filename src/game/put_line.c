#include "../includes/cub3d.h"

int	touch_wall(float pcol, float prow, t_cub *cub)
{
	int	j;
	int	i;

	i = (prow - cub->minimap->start_x) / MINIMAP_TILE_SIZE;
	j = pcol / MINIMAP_TILE_SIZE;
	if (i < 0 || i >= cub->map->rows || j < 0 || j >= cub->map->cols)
		return (1); // Treat out-of-bounds as a wall
	if (cub->map->map[i][j] == '1')
		return (1);
	return (0);
}
static float    distance(float row2, float row1, float col2, float col1, t_cub *cub)
{
    float   delta_row;
    float   delta_col;
    float   distance;
    delta_row = (row1 - row2);
    delta_col = (col1 - col2);
    distance = sqrt(delta_row * delta_row + delta_col * delta_col);
    // printf("Player Position: (%f, %f), Ray Hit: (%f, %f), Distance: %f\n", row1, col1, row2, col2, distance);
    //this distances has a fisheye effect this fix
    float angle = atan2(delta_col, delta_row)- cub->map->player->angle; //POSIBLE BUG
    float fix_distance = fabs(distance * cos(angle));
    // printf("dist: %f, fixed: %f\n", distance, fix_distance);
    return (fix_distance);
}


static float whileTouch(t_player *player, t_cub *cub, float cos_angle, float sin_angle, int color)
{
    t_imgen image;
    float   ray_row;
    float   ray_col;
    image.img = NULL;
    const float player_row = player->map_row * MINIMAP_TILE_SIZE + cub->minimap->start_x
        + MINIMAP_TILE_SIZE / 2;
    const float player_col  = player->map_col * MINIMAP_TILE_SIZE + MINIMAP_TILE_SIZE / 2;
    ray_row = (float)player_row;
    ray_col = (float)player_col;
    // FOV on minimap
    while (!touch_wall(ray_col, ray_row, cub))
    {
		if (cub->options.show_minimap == 1)
        	put_pixel((int)ray_col, (int)ray_row, color, cub);
        ray_row += cos_angle;
        ray_col += sin_angle;
    }
    //perspective
    return distance(ray_row, player_row, ray_col, player_col, cub);
}

static void	put_texture(t_cub *cub, int col, int end)
{
	int	i;
	int	col_texture;

	i = 0;
	col_texture = col % 4;
	while (i < (PIXEL_SIZE - 1))
	{
		printf("hola texture %d\n", cub->textures->text[0][i]);
		put_pixel(col, end, cub->textures->text[0][i], cub);
		i++;
	}
}

void    put_line(t_player *player, t_cub *cub, float angle, int i, int color)
{
    float   cos_angle;
    float   sin_angle;
    t_imgen image;
    float   dist;
    float   wall_height;
    int     start_row;
    int     end_row;
    image.img = NULL;
    cos_angle = cos(angle);
    sin_angle = sin(angle);
    dist = whileTouch(player, cub, cos_angle, sin_angle, color);
    if(dist > 0.1)
        wall_height = (WIN_HEIGHT * 16) / dist; // * (WIN_WIDTH / 2);  //WALL_SIZE
    else
        wall_height = (WIN_HEIGHT * 16); // * (WIN_WIDTH / 2);  //WALL_SIZE
    // start_row = (WIN_HEIGHT - wall_height) / 2;
    // end_row = start_row + wall_height;
    // printf("dist, start: %f\n", dist);
    start_row = ((WIN_HEIGHT - wall_height) / 2);
    end_row = (start_row + wall_height);
    //printf("la i %d- starwor%d -  endrow %d\n", i, start_row ,end_row);
    while (end_row > start_row)
    {
        //hay que controlar que no dibuje encima del minimapa
        put_pixel(i, end_row, cub->textures->text[0][ end_row * PIXEL_SIZE + i], cub);
        //put_texture(cub, i, end_row);
        //set_image_pixel(&image, start_row, end_row, cub->textures->text[start_row][end_row]);
        end_row--;
    }
}

// TODO: call to player->win_x and player_>win_y on the start of the rays
void	minimap_put_axis(t_cub *cub, int color)
{
	t_player	*player;
	float		ray_row;
	float		ray_col;
	float		cos_angle;
	float		sin_angle;

	// printf("minimap_put_axis\n");
	player = cub->map->player;
	ray_row = player->map_row * MINIMAP_TILE_SIZE + cub->minimap->start_x
		+ MINIMAP_TILE_SIZE / 2;
	ray_col = player->map_col * MINIMAP_TILE_SIZE + MINIMAP_TILE_SIZE / 2;
	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	while (!touch_wall(ray_col, ray_row, cub))
	{
		if (cub->options.show_minimap == 1)
			put_pixel((int)ray_col, (int)ray_row, color, cub);
		ray_row += cos_angle;
		ray_col += sin_angle;
	}
}

// TODO: add FOV to options so we can change it with a hook
void	put_camera(t_cub *cub)
{
	t_player	*player;
	const float	FOV = PI / 6;
	float		fraction;
	float		start_angle;
	int			screen_col_idx;

	player = cub->map->player;
	fraction = (FOV * 2) / WIN_WIDTH;
	//(FOV * 2) / (cub->map->cols * MINIMAP_TILE_SIZE)
	start_angle = player->angle - FOV;
	screen_col_idx = WIN_WIDTH;
	// i < (cub->map->cols * MINIMAP_TILE_SIZE)
	while (screen_col_idx > 0)
	{	
		int color = 0xAA6666;
		// printf("put_line(player, cub, angle, i, color): (%p, %p, %f, %d, %d)\n", player, cub, start_angle, screen_col_idx, color);
		put_line(player, cub, start_angle, screen_col_idx, color);
		//previous color: 255
		start_angle += fraction;
		screen_col_idx--;
	}
	// render_frame(cub); //TODO revisar
}
