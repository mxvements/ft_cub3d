/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlu <zlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:06:16 by luciama2          #+#    #+#             */
/*   Updated: 2025/03/08 11:23:56 by zlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (print_error("main", ERR_USE));
	if (ft_strncmp(argv[1], "test\0", 5) == 0)
		return (parse_test());
	if (init_cub_game(argv[1]) < 0)
		return (1);
	return (0);
}
