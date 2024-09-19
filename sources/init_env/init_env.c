/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 09:20:33 by fberthou          #+#    #+#             */
/*   Updated: 2024/09/19 18:29:45 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	close_win(t_map_data *map, int key_code)
{
	(void) key_code;
	return (mlx_loop_end(map->console.mlx_ptr));
}

static int	key_hook(int keycode, t_map_data *map)
{
	if (keycode == XK_Escape)
		return (free_all(map), 0);
	return (0);
}

static void	hook_management(t_map_data *map)
{
	mlx_hook(map->console.win_ptr, DestroyNotify, StructureNotifyMask, \
														&close_win, map);
	mlx_key_hook(map->console.win_ptr, key_hook, map);
	return ;
}

static int	init_console(t_map_data *map)
{
	map->console.mlx_ptr = mlx_init();
	if (!map->console.mlx_ptr)
		return (ft_perror("Console initialisation\n"), 1);
	map->console.win_ptr = mlx_new_window(map->console.mlx_ptr, 1920, 1000, \
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
	if (init_console(map))
		return (1);
	hook_management(map);
	mlx_loop(map->console.mlx_ptr);
	return (0);
}

