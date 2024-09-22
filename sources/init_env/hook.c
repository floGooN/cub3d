/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 12:52:49 by florian           #+#    #+#             */
/*   Updated: 2024/09/21 12:54:38 by florian          ###   ########.fr       */
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
		return (mlx_loop_end(map->console.mlx_ptr));
	return (0);
}

void	hook_management(t_map_data *map)
{
	mlx_hook(map->console.win_ptr, DestroyNotify, StructureNotifyMask, \
														&close_win, map);
	mlx_key_hook(map->console.win_ptr, key_hook, map);
	return ;
}
