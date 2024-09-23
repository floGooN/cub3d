/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 12:52:49 by florian           #+#    #+#             */
/*   Updated: 2024/09/23 09:54:06 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	close_win(t_map_data *map, int key_code)
{
	(void) key_code;
	return (mlx_loop_end(map->console.mlx_ptr));
}

int key_up(int code, t_map_data *map)
{
	if (code == XK_Escape)
		return (mlx_loop_end(map->console.mlx_ptr));
	else if (code == 'w')
		map->player.move_up = 0;
	else if (code == 's')
		map->player.move_down = 0;
	else if (code == 'a')
		map->player.move_left = 0;
	else if (code == 'd')
		map->player.move_right = 0;
	else if (code == 65361)
		map->player.rotate_left = 0;
	else if (code == 65363)
		map->player.rotate_right = 0;
	return (0);
}

int key_down(int code, t_map_data *map)\
{
	if (code == XK_Escape)
		return (mlx_loop_end(map->console.mlx_ptr));
	else if (code == 'w')
		map->player.move_up = 1;
	else if (code == 's')
		map->player.move_down = 1;
	else if (code == 'a')
		map->player.move_left = 1;
	else if (code == 'd')
		map->player.move_right = 1;
	else if (code == 65361)
		map->player.rotate_left = 1;
	else if (code == 65363)
		map->player.rotate_right = 1;
	return (0);
}

void	hook_management(t_map_data *map)
{
	mlx_hook(map->console.win_ptr, DestroyNotify, StructureNotifyMask, \
														close_win, map);
    mlx_hook(map->console.win_ptr, KeyPress, KeyPressMask, key_down, map);
    mlx_hook(map->console.win_ptr, KeyRelease, KeyReleaseMask, key_up, map);
	return ;
}
