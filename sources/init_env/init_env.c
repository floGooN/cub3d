/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 09:20:33 by fberthou          #+#    #+#             */
/*   Updated: 2024/09/25 07:59:22 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void    init_player(t_map_data *map)
{
    map->player.pos_x = 31 * CELL_SIZE;
    map->player.pos_y = 3 * CELL_SIZE;
	if (map->player.dir == NORTH)
    {
        INIT_PLAYER(0, -1, 3 * M_PI_2);
    }
    else if (map->player.dir == SOUTH)
    {
        INIT_PLAYER(0, 1, M_PI_2);
    }
    else if (map->player.dir == EAST)
    {
        INIT_PLAYER(1, 0, 0);
    }
    else if (map->player.dir == WEST)
    {
        INIT_PLAYER(-1, 0, M_PI);
    }
}

static int	init_console(t_map_data *map, int width, int height)
{
    map->console.win_width = WIN_WIDTH;
    map->console.win_height = WIN_HEIGHT;
	map->console.mlx_ptr = mlx_init();
	if (!map->console.mlx_ptr)
		return (ft_perror("Console initialisation\n"), 1);
	map->console.win_ptr = mlx_new_window(map->console.mlx_ptr, 1300, 750, \
							"==== CUB3D ====");
	if (!map->console.win_ptr)
	{
		mlx_destroy_display(map->console.mlx_ptr);
		free(map->console.mlx_ptr);
		return (ft_perror("window initialisation\n"), 1);
	}
	return (0);
}

int	init_env(t_map_data *map)
{
	if (init_console(map, map->console.win_width, map->console.win_height))
		return (1);
    init_player(map);
	hook_management(map);
	return (0);
}
