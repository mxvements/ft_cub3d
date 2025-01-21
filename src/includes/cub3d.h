#ifndef CUB3D_H
# define CUB3D_H

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

# include "../../libft/libft.h"
# include "../../gnl/get_next_line.h"
# include "../../minilibx-linux/mlx.h"
# include "colors.h"
# include "error_msg.h"
# include "minimap.h"
# include "linux_keys.h"

# define	WALL_SIDES	4
# define	DEBUG		1 //for the print_error 
# define	PIXEL_SIZE	128 // ¿que es esto?
# define	IMG_SIZE	10
# define	WIN_HEIGHT	540
# define 	WIN_WIDTH	960
# define 	MINIMAP_TILE_SIZE	16
# define	TILE_SIZE 32

# define PI 3.14159265359

enum e_texure_index
{
	NORTH,	// 0
	SOUTH,	// 1
	WEST,	// 2
	EAST	// 3
} ; 

typedef struct s_texture
{
	char		*wall[WALL_SIDES]; // use enum to know wich side of wall
	long long	floor;
	long long	ceiling;
} t_texture;

typedef struct s_move_keys
{
	int key_up;
    int key_down;
    int key_left;
    int key_right;
    int left_rotate;
    int right_rotate;
} t_move_keys;

typedef struct s_minimap
{
	float	start_x; //start of the drawing of the map in the img
	void	*img_wall;
	void	*img_floor;
	void	*img_player;
	void	*img_void;
}	t_minimap;

typedef struct s_player
{
    float	map_x;
    float	map_y;
	float	angle;
	t_move_keys	move_keys;
}	t_player;

typedef struct s_map
{
	char 		**map; //two dimensional array
	char		old_position;
	t_player	*player;
	int			rows;
	int			cols;
	int			size;
}	t_map;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win;
	void	*img;
	char	*img_addr;
	int		bpp; //bits per pixel
	int		line_len;
	int		endian;
}	t_mlx;

typedef struct s_options
{
	int		wall_col;
	int		show_minimap;
	float	move_speed;
	float	rotate_speed;
} t_options;

typedef struct s_cub
{
	int			count;
	t_mlx		*mlx;
	t_map 		*map;
	t_minimap	*minimap;
	t_texture	*textures;
	t_options	options;
	int			fd;
}	t_cub ;



int	init_cub_game(char *filepath);
int init_mlx(t_cub *cub);

/* PARSING */
int		parse_input(t_cub *cub, char *filepath);
int		parse_texture_and_colors(t_texture *tx, int fd);
int		parse_map(t_map *map, int fd);
int		is_file_extension(char *filepath, char *extension);
int		is_texture_struct_full(t_texture *tx);
int		is_player(t_player *player);
int		is_player_on_edge(t_map *map, t_player *player);
int		is_color(char **rgb);
int		is_permitted_char(char *line);
int		is_map_eof(int fd);
int		check_map(t_map *map);

/* UTILS*/
long long	color_str_to_long(char **rgb);
char		*strtrim_gnl(int fd, char *trim);
void		clean_gnl(int fd);

/* ERRORS */
int		print_error(char *origin, char *custom_msg);

/* UTILS */
int		free_cub(t_cub *cub);
void	free_map(void *data);
void	print_cub(t_cub *cub);
void	print_player(t_player *pl);
void	print_texture(t_texture *tx);
void	print_minimap(t_minimap *minimap);
void	print_map(t_map *map);
void	print_options_status(t_options *options);
char	*ft_concat(char *first, ...); //at add_minimap.c

/* PARSING TEST */
int	parse_test(void);

/* game */
void	ray(t_cub *data);
void	insert_img(t_cub *data, t_map *map);
void	mapok(char **res, t_cub *data, int i, int j);
void	render(t_cub *mlx, t_map *map);
int 	init_engine(t_cub *cub);
// int		del_data(t_cub *data);
void	move_and_rotate(t_cub *data);
char	*read_map(char *s);
void	positionPlayer(t_cub *data);

/* MINIMAP*/
// int	add_minimap(t_cub *cub);
int		minimap_init(t_cub *cub);
int		minimap_render(t_cub *cub);
void	minimap_put_str(t_cub *cub);
int		minimap_set_img(t_cub *cub);


/* DRAW */
void	put_pixel(int col, int row, int color, t_cub *cub);
void	put_square(int row, int col, int size, int color, t_cub *cub);
void	minimap_put_axis(t_cub *cub, int color);
void	minimap_put_player(t_cub *cub, int color);
void	put_line(t_player *player, t_cub *game, float start_x, int i,
		int color);
void 	put_tile(t_cub *cub, void *tile_img, int row_offset, int col_offset);
void	put_camera(t_cub *cub);
#endif