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

#define	WALL_SIDES	4

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

typedef struct s_map
{
	char	*path;
	char	*map1d; //de edu para borrar cuando tengamos parseo
	char 	**map; //two dimensional array
	int		rows;
	int		cols;
	int		size;
	void	*img_pared;
	void	*img_arena;
	void	*img_people;
	char	*path_pared;
	char	*path_arena;
	char	*path_aladin;
} t_map;

typedef struct s_player
{
    float           x; //parseo (N.S.E.W)
    float           y; //parseo (N)
    float           dirX; //parseo, dar vector
    float           dirY; //parseo, dar vector
    int             a;
    int             wolk;   //andar 0 parado, 1 para delante, -1 para atras
    int             spin;   //girar 1 derecha, -1 izquierda
}                   t_player;

typedef struct s_cub
{
	void		*mlx;
	void		*win;
	int			count;
	t_map 		*map;
	t_texture	*textures;
	t_player	*player;
	int			fd;
} t_cub ;

/* PARSING */
t_cub		*parse_input(t_cub *cub, char *filepath);
int			parse_texture_and_colors(t_texture *tx, int fd);
int			parse_map(t_map *map, int fd);
int			check_file_extension(char *filepath, char *extension);
int			check_color(char **rgb);
int			check_permitted_char(char *line);
int			check_map(t_map *map);
long long	color_str_to_long(char **rgb);

/* ERRORS */
int		print_error(char *custom_msg);

/* develop */
void    testprintMap(char **map);

/* game */
void	ray(t_cub *data);
void	insect_img(t_cub *data, t_map *map);
void	mapok(char **res, t_cub *data, int i, int j);
void	ini(t_cub *data);
void	print_map(t_cub *mlx, t_map *map);
int		del_data(t_cub *data);
void	move(t_cub *data, int x, int y);
char	*read_map(char *s);
void	positionPlayer(t_cub *data);


#endif