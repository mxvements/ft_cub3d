#ifndef ERROR_MSG
# define ERROR_MSG

# define ERR_USE "usage: ./cube3d <path/to/map.cub>"
# define ERR_CUB "file should have '.cub' extension"
# define ERR_FD "Error reading input file"
# define ERR_TXT "All textures should have '.xpm' extension"

# define ERR_TXT_NORTH "North texture should have '.xpm' extension"
# define ERR_TXT_SOUTH "South texture should have '.xpm' extension"
# define ERR_TXT_WEST "West texture should have '.xpm' extension"
# define ERR_TXT_EAST "East texture should have '.xpm' extension"
# define ERR_COL_F "Floor must be a color with 3 numbers"
# define ERR_COL_C "Ceiling must be a color with 3 numbers"

# define ERR_MAP_SPC "Wrong map, all ' ' should be surrounded by {'1',' '}"
# define ERR_MAP_0 "Wrong map, all '0' should be surrounded by {'0','1'}"
# define ERR_MAP_BOUNDS \
	"Wrong map, the first/last lines should only have {'1',' '}"
# define ERR_MAP_CHAR \
	"Wront char, map should only contain {'0','1',' '} \
	and the player position {'N','E','S','W'}"

#endif