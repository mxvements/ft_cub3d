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
}	t_texture;

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
}	t_map;


typedef struct s_mlx
{
	void	*mlx;
	void	*mlx_win;
	void	*img;
	char	*img_addr;
	int		bpp; //bits per pixel
	int		line_len;
	int		endian;
}	t_mlx;

typedef struct s_cub
{
	t_mlx		mlx; //pointer?
	t_map 		*map;
	t_texture	*textures;
	int			fd;
}	t_cub ;



int	init_cub_game(char *filepath);

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

#endif