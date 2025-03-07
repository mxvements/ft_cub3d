/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciama2 <luciama2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:06:45 by luciama2          #+#    #+#             */
/*   Updated: 2025/03/07 20:06:46 by luciama2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../../gnl/get_next_line.h"
# include "../../libft/libft.h"
# include "../../minilibx-linux/mlx.h"
# include "minimap.h"
# include "colors.h"
# include "error_msg.h"
# include "linux_keys.h"
# include <limits.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <fcntl.h>
# include <string.h>
# include <sys/time.h>
# include <errno.h>
# include <math.h>

# define WALL_SIDES 4
# define MOVE_MAX 1
# define DEBUG 1 //for the print_error 
# define IMG_PX 64 // tamaño de imagen en un cuadrado
# define MINIMAP_PX 16
# define WIN_HEIGHT 540
# define WIN_WIDTH 960
# define MINIMAP_RADIUS 10 //tiles


# define PI 3.14159265359

enum			e_texture_index
{
	NORTH,
	SOUTH,
	WEST,
	EAST
};

enum			e_collision
{
	VERTICAL,
	HORIZONTAL
};

typedef struct s_texture
{
	char		*wall[WALL_SIDES];
	int			*text[WALL_SIDES];
	int			**pixel;
	long long	floor;
	long long	ceiling;
}				t_texture;

typedef struct s_move_keys
{
	int			key_up;
	int			key_down;
	int			key_left;
	int			key_right;
	int			left_rotate;
	int			right_rotate;
}				t_move_keys;

typedef struct s_minimap
{
	float	start_x;
	float	end_y;
	void	*img_wall;
	void	*img_floor;
	void	*img_player;
	void	*img_void;
}	t_minimap;

typedef struct s_image
{
	t_img	*img;
	int		*addr;
	int		pixel_bits;
	int		size_line;
	int		endian;
}	t_image;

typedef struct s_player
{
	float				map_row;
	float				map_col;
	float				win_row;
	float				win_col;
	float				angle;
	struct s_move_keys	move_keys;
}				t_player;

typedef struct s_map
{
	char		**map;
	char		old_char;
	t_player	*player;
	int			rows;
	int			cols;
	int			size;
}				t_map;

typedef struct s_mlx
{
	void		*mlx_ptr;
	void		*win;
	void		*img;
	char		*img_addr;
	int			bpp;
	int			line_len;
	int			endian;
}				t_mlx;

typedef struct s_options
{
	int			wall_col;
	int			show_minimap;
	float		move_speed;
	float		rotate_speed;
	float		fov;
}				t_options;

typedef struct s_hit
{
	float	dist;
	int		map_tile[2]; //[0] == row, [1] == col
	float	ray[2];
	float	angle;
	int		texture_idx;
	int		collision_dir;
}	t_hit;

typedef struct s_cub
{
	int			count;
	t_mlx		*mlx;
	t_map		*map;
	t_minimap	*minimap;
	t_texture	*textures;
	t_options	options;
	t_hit		hits[WIN_WIDTH];
	float		dist[WIN_WIDTH];
	int			fd;
}				t_cub;

int			init_cub_game(char *filepath);
int			init_mlx(t_cub *cub);

/* PARSING */
int			parse_input(t_cub *cub, char *filepath);
int			parse_texture_and_colors(t_texture *tx, int fd);
int			parse_map(t_map *map, int fd);
int			is_file_extension(char *filepath, char *extension);
int			is_texture_struct_full(t_texture *tx);
int			is_player(t_player *player);
int			is_player_on_edge(t_map *map, t_player *player);
int			is_color(char **rgb);
int			is_permitted_char(char *line);
int			is_map_eof(int fd);
int			check_map(t_map *map);
char		*get_prefix(int i);

/* UTILS*/
long long	color_str_to_long(char **rgb);
char		*strtrim_gnl(int fd, char *trim);
void		clean_gnl(int fd);
void		free_map(void *data);
void		free_struct(void **s, void (*free_s)(void *));
void		free_int_ptr(int **ptr);

/* ERRORS */
int			print_error(char *origin, char *custom_msg);

/* UTILS */
int			free_cub(t_cub *cub);
void		print_cub(t_cub *cub);
void		print_player(t_player *pl);
void		print_texture(t_texture *tx);
void		print_minimap(t_minimap *minimap);
void		print_map(t_map *map);
void		print_options_status(t_options *options);
void		print_key_options(t_cub *cub);
char		*ft_concat(char *first, ...); // at add_minimap.c

/* PARSING TEST */
int			parse_test(void);

/* GAME */
int			init_engine(t_cub *cub);
void		move_and_rotate(t_cub *data);
int			is_touching_wall(float pcol, float prow, t_cub *cub);
void		get_distance(t_cub *cub, float cos, float sin, int i);
void		put_perspective(t_cub *cub);
void		texture_ceiling(t_cub *cub, int start_row, int i);
void		texture_floor(t_cub *cub, int end_row, int i);
float		wall_offset(t_cub *cub, int i);

/* HOOKS */
int			key_release(int keycode, t_cub *cub);
int			key_press(int keycode, t_cub *cub);
int			win_close(t_cub *cub);

/* MINIMAP*/
int			minimap_init(t_cub *cub);
int			minimap_render(t_cub *cub);
void		minimap_put_str(t_cub *cub);
int			minimap_set_img(t_cub *cub);
void		minimap_put_player(t_cub *cub, int color);
void		minimap_put_axis(t_cub *cub, int color_axis);
void		minimap_put_fov(t_cub *cub, int color_fov);

/** WALL TEXTURES */
int			init_textures(t_cub *data);
int			init_img(t_cub *data, t_image *image, int width, int height);
void		set_frame_image_pixel(t_cub *data, t_image *image, int x, int y);
void		set_image_pixel(t_image *image, int x, int y, int color);
void		render_frame(t_cub *data);
void		init_texture_pixels(t_cub *data);

/* DRAW */
void		put_pixel(int col, int row, int color, t_cub *cub);
void		put_tile(t_cub *cub, void *tile_img, int row_offset, \
			int col_offset);
void	put_partial_tile(t_cub *cub, void *tile_img, int row_offset,
		int col_offset);
void		put_square(int prow, int pcol, int color, t_cub *cub);

/* TEST */
int			test_colors(void);
int			test_textures(void);

#endif