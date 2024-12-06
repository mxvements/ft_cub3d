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
	int			fd;
	char		*path;
	char 		**map; //two dimensional array
	long long	height;
	long long	width;
} t_map;

typedef struct s_cub
{
	void		*mlx;
	t_map 		*map;
	t_texture	*textures;
} t_cub ;

/* PARSING */
t_cub		*parse_input(t_cub *cub, char *filepath);
int			parse_texture_and_colors(t_texture *tx, int fd);
int			check_file_extension(char *filepath, char *extension);
int			check_color(char **rgb);
long long	color_str_to_long(char **rgb);

/* ERRORS */
void	print_error(char *custom_msg);

#endif