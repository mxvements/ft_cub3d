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

# include "colors.h"
# include "error_msg.h"

enum e_texure_index
{
	NORTH,	// 0
	SOUTH,	// 1
	WEST,	// 2
	EAST	// 3
} ; 

typedef struct s_texture
{
	char	*wall[4]; // use enum to know wich side of wall
	char	*floor;
	char	*ceiling;
} t_texture;

typedef struct s_map
{
	int		fd;
	char	*path;
	int		height;
	int		width;
} t_map;

typedef struct s_cub
{
	void		*mlx;
	t_map 		*map;
	t_texture	*textures;
} t_cub ;


void	print_error(char *custom_msg);

#endif