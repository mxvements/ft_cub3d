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

typedef struct s_texture
{
	char		*wall[WALL_SIDES]; // use enum to know wich side of wall
	long long	floor;
	long long	ceiling;
} t_texture;

typedef struct s_map
{
	char	*path;
	int 	**map; //two dimensional array
	int		height;
	int		width;
} t_map;

typedef struct s_cub
{
	void		*mlx;
	t_map 		*map;
	t_texture	*textures;
	int			fd;
} t_cub ;

/* PARSING */
t_cub		*parse_input(t_cub *cub, char *filepath);
int			parse_texture_and_colors(t_texture *tx, int fd);
int			parse_map(t_map *map, int fd);
int			check_file_extension(char *filepath, char *extension);
int			check_color(char **rgb);
int			check_map(char **map);
long long	color_str_to_long(char **rgb);

/* ERRORS */
int		print_error(char *custom_msg);

#endif