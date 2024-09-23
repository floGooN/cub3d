/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 09:20:33 by fberthou          #+#    #+#             */
/*   Updated: 2024/09/23 16:14:10 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void    put_player(t_map_data *map)
{
    int p_color = 0xFF0000;
    double radius  = 5;
    double center_x = map->player.player_x + radius;
    double center_y = map->player.player_y + radius;

	// put player in 2d map
	for (int y = 0; y < radius * 2; y++){
		for (int x = 0; x < radius * 2; x ++){
			if (sqrt(pow(x - radius, 2) + pow(y - radius, 2)) <= radius)
				mlx_pixel_put(map->console.mlx_ptr, map->console.win_ptr, center_x - (x - radius), center_y - (y - radius), p_color);
		}
	}
	// put player direction
	if (map->player.dir == NORTH){

	}
	else if (map->player.dir == SOUTH){

	}
	else if (map->player.dir == EAST){

	}
	else if (map->player.dir = WEST){

	}
    return ;
}

void	put_square(t_map_data *map, int color, int y, int x)
{
    int start_y;
    int start_x;

    start_y = y * CELL_HEIGTH;
    start_x = x * CELL_WIDTH;
	for (int i = 0; i < CELL_HEIGTH; i++)
	{
		mlx_pixel_put(map->console.mlx_ptr, map->console.win_ptr, start_x + i, start_y, color);
		for (int j = 0; j < CELL_WIDTH; j++){
			mlx_pixel_put(map->console.mlx_ptr, map->console.win_ptr, start_x + i, start_y + j, color);
		}
	}
	return ;
}

void	put_map(t_map_data *map)
{
	int	color;

	for (int y = 0; y < 15 ; y++)
	{
		for (int x = 0; x < 35; x++)
		{
			if (map->map[y][x] == '1')
				color = 0xFFFFFF; // white for walls
			else
				color = 0x000000; // black for empty spaces
			put_square(map, color, y, x);
		}
	}
    put_player(map);
}

int	update_player_pos(t_map_data *map)
{
	if (map->player.move_down)
	{
		if (map->player.player_y < 14 * CELL_WIDTH - (CELL_HEIGTH + 12))
			map->player.player_y += SPEED;
	}
	if (map->player.move_up)
	{
		if (map->player.player_y > 0 + CELL_WIDTH)
			map->player.player_y -= SPEED;
	}
	if (map->player.move_left)
	{
		if (map->player.player_x > 0 + CELL_WIDTH)
			map->player.player_x -= SPEED;
	}
	if (map->player.move_right)
	{
		if (map->player.player_x < ft_strlen(map->map[0]) * CELL_WIDTH - (CELL_WIDTH + 12))
			map->player.player_x += SPEED;
	}
	return (0);
}

int	loop_hook(t_map_data *map)
{
	if (map->player.move_down || map->player.move_up || \
		map->player.move_left || map->player.move_right || \
		map->player.rotate_left || map->player.rotate_right)
	{
		update_player_pos(map);
		put_map(map);
	}
	return (0);
}

static int	init_console(t_map_data *map, int width, int height)
{
	map->console.mlx_ptr = mlx_init();
	if (!map->console.mlx_ptr)
		return (ft_perror("Console initialisation\n"), 1);
	map->console.win_ptr = mlx_new_window(map->console.mlx_ptr, width, height, \
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
    map->console.win_width = WIN_WIDTH;
    map->console.win_height = WIN_HEIGHT;
	map->player.player_x = 26 * CELL_WIDTH;
    map->player.player_y = 11 * CELL_HEIGTH;
	if (init_console(map, map->console.win_width, map->console.win_height))
		return (1);
	hook_management(map);
	put_map(map);
	mlx_loop_hook(map->console.mlx_ptr, loop_hook, map);
	mlx_loop(map->console.mlx_ptr);
	return (0);
}
