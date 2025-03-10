/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciama2 <luciama2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:04:27 by luciama2          #+#    #+#             */
/*   Updated: 2025/03/07 20:04:28 by luciama2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	print_error(char *origin, char *custom_msg)
{
	printf(RED"Error\n");
	if (DEBUG == 1)
		printf(RED"%s - "RESET, origin);
	if (custom_msg)
		printf(RED"%s (errno: %d)\n"RESET, custom_msg, errno);
	else
		printf(RED"%s (errno %d)\n"RESET, strerror(errno), errno);
	return (-1);
}
