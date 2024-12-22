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

# define	WALL_SIDES	4
# define	DEBUG		1
# define	PIXEL_SIZE	128
# define	IMG_SIZE	10
# define	WIN_HEIGHT	540
# define 	WIN_WIDTH	860

enum e_texure_index
{
	NORTH,	// 0
	SOUTH,	// 1
	WEST,	// 2
	EAST	// 3
} ; 

enum {
	key_W=119,
	key_A=97,
	key_S=115,
	key_D=100,
	key_LEFT=65361,
	key_DOWN=65364,
	key_RIGHT=65363,
	key_UP=65362,
	key_SPACE=32,
	key_R=114,
	key_ESC = 65307
};


typedef struct s_texture
{
	char		*wall[WALL_SIDES]; // use enum to know wich side of wall
	long long	floor;
	long long	ceiling;
} t_texture;

typedef struct s_minimap
{
	void	*img_wall;
	void	*img_floor;
	void	*img_player;
	char	*path_wall;
	char	*path_floor;
	char	*path_player;

}	t_minimap;

typedef struct s_player
{
    float           x; //parseo (N.S.E.W)
    float           y; //parseo (N)
    float           dirX; //parseo, dar vector
    float           dirY; //parseo, dar vector
    int             a;
    int             walk;   //andar 0 parado, 1 para delante, -1 para atras
    int             spin;   //girar 1 derecha (cv), -1 izquierda (ccw)
}	t_player;

typedef struct s_map
{
	char 		**map; //two dimensional array
	t_player	*player;
	int			rows;
	int			cols;
	int		size;

}	t_map;


typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*img_addr;
	int		bpp; //bits per pixel
	int		line_len;
	int		endian;
}	t_mlx;

typedef struct s_cub
{
	t_mlx		*mlx;
	int			count;
	t_map 		*map;
	t_minimap	*minimap;
	t_texture	*textures;
	int			fd;
}	t_cub ;



int	init_cub_game(char *filepath);
void init_mlx(t_cub *cub);

/* PARSING */
int		parse_input(t_cub *cub, char *filepath);
int		parse_texture_and_colors(t_texture *tx, int fd);
int		parse_map(t_map *map, int fd);
int		is_file_extension(char *filepath, char *extension);
int		is_texture_struct_full(t_texture *tx);
int		is_player(t_player *player);
int		is_color(char **rgb);
int		is_permitted_char(char *line);
int		check_map(t_map *map);

/* UTILS*/
long long	color_str_to_long(char **rgb);
char		*strtrim_gnl(int fd, char *trim);

/* ERRORS */
int		print_error(char *origin, char *custom_msg);

/* UTILS */
int		free_cub(t_cub *cub);
void	free_map(t_map *map);
void	print_cub(t_cub *cub);
void	print_player(t_player *pl);
void	print_texture(t_texture *tx);
void	print_map(t_map *map);

/* PARSING TEST */
int	parse_test(void);

/* develop */
void    testprintMap(char **map); //remove

/* game */
void	ray(t_cub *data);
void	insect_img(t_cub *data, t_map *map);
void	mapok(char **res, t_cub *data, int i, int j);
void	render_map(t_cub *mlx, t_map *map);
void	init_minimap(t_cub *data);
int		del_data(t_cub *data);
void	move(t_cub *data, int x, int y);
char	*read_map(char *s);
void	positionPlayer(t_cub *data);


#endif