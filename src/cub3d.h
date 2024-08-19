

#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx.h"
# include "../Libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_map
{
	char		*map;
	char		**map2d;
}					t_map;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	int			x_max;
	int			y_max;
	int			size;
	int			steps;
	int			x;
	int			y;
	t_map		*map;
}					t_data;

enum {
	key_W=119,
	key_A=97,
	key_S=115,
	key_D=100,
	key_LEFT=65361,
	key_DOWN=65364,
	key_RIGHT=65363,
	key_UP=65362,
	key_SPACE=65, // pendiente de confirmar
	key_ESC = 65307
};

#endif