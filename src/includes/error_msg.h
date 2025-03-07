/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciama2 <luciama2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:06:48 by luciama2          #+#    #+#             */
/*   Updated: 2025/03/07 20:06:49 by luciama2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_MSG_H
# define ERROR_MSG_H

/* MAIN ERRORS */
# define ERR_USE "usage: ./cube3d <path/to/map.cub>"
# define ERR_CUB "file should have '.cub' extension"
# define ERR_FD "Error reading input file"

/* TEXTURE ERRORS */
# define ERR_TXT "All textures should have '.xpm' extension"
# define ERR_TXT_MISSING \
	"Missing XPM: any of the textures for the wall orientations"
# define ERR_TXT_DUPL "Duplicate XPM: duplicate textures on the file"
# define ERR_COL_MISSING "Missing RGB: ceiling and/or floor colors"
# define ERR_TXT_NORTH "North texture should have '.xpm' extension"
# define ERR_TXT_SOUTH "South texture should have '.xpm' extension"
# define ERR_TXT_WEST "West texture should have '.xpm' extension"
# define ERR_TXT_EAST "East texture should have '.xpm' extension"

/* COLOR ERRORS */
# define ERR_COL_F \
	"Invalid/Incomplete RGB: \
	Floor must be a color with 3 numbers in the range 0..255"
# define ERR_COL_C \
	"Invalid/Incomplete RGB: \
	Ceiling must be a color with 3 numbers in the range 0..255"

/* MAP ERRORS */
# define ERR_MAP_MISSING "Missing map."
# define ERR_MAP_SIZE "Map too small: there must be more than 3 cols or rows."
# define ERR_MAP_END \
	"EOF must end with empty lines or the last line of the map. \
	Single line with ascii found."
# define ERR_MAP_SPC "Wrong map, all ' ' should be surrounded by {'1',' '}"
# define ERR_MAP_0 "Wrong map, all '0' should be surrounded by {'0','1'}"
# define ERR_MAP_0_EDGE "Wrong map, '0' on map edge."
# define ERR_MAP_BOUNDS \
	"Wrong map, the first/last lines should only have {'1',' '}"
# define ERR_MAP_CHAR \
	"Wront char, map should only contain {'0','1',' '} \
	and the player position {'N','E','S','W'}"

/* PLAYER ERRORS */
# define ERR_PL_MULT	"Wrong map, multiple players found."
# define ERR_PL_MISSING "Wrong map, Missing player."
# define ERR_PL_EDGE "Wrong map, Player on edge wall."

/* MINIMAp */
# define ERR_MINI_IMG	"Error initializing xpm file to image"

#endif