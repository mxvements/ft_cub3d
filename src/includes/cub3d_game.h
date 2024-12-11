

#ifndef CUB3D_GAME_H
# define CUB3D_GAME_H

# include "cub3d.h"

// # include "../../minilibx-linux/mlx.h"
// # include "../../minilibx-linux/mlx_int.h"

typedef struct s_map_game
{
	char		*map;
	char		**map2d;
	char		NO_texture;
	char		SO_texture;
	char		WE_texture;
	char		EA_texture;
	int			floor;
	int			ceiling;
	void		*img_pared;
	void		*img_arena;
	void		*img_people;
	char		*path_pared;
	char		*path_arena;
	char		*path_aladin;
	
}					t_map_game;

typedef struct	s_data_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data_img;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	int			x_max;
	int			y_max;
	int			size;
	int			steps;
	int			sp_spin;
	int			count;
	t_map_game	*map;
	t_player	*player;
	t_data_img	*img;
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
	key_SPACE=32,
	key_R=114,
	key_ESC = 65307
};

//adicional
void    testprintMap(char **map);

//funciones
void	ray(t_data *data);
void	insect_img(t_data *data, t_map_game *map);
void	mapok(char **res, t_data *data, int i, int j);
void	ini(t_data *data);
void	print_map_game(t_data *mlx, t_map_game *map);
int		del_data(t_data *data);
void	move(t_data *data, int x, int y);
char	*read_map(char *s);
void	positionPlayer(t_data *data);

#endif