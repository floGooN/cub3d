/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 09:20:33 by fberthou          #+#    #+#             */
/*   Updated: 2024/09/23 10:00:05 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void    put_player(t_map_data *map)
{
    int p_color = 0xFF0000;
    int radius  = 5;
    int center_x = map->player.player_x + radius;
    int center_y = map->player.player_y + radius;

    for (int y = 0; y < radius * 2; y++){
		for (int x = 0; x < radius *2; x ++){
			if (sqrt(pow(x - radius, 2) + pow(y - radius, 2)) <= radius)
        		mlx_pixel_put(map->console.mlx_ptr, map->console.win_ptr, center_x - (x - radius), center_y - (y - radius), p_color);
		}
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

int	update_player_pos(t_map_data *map)
{
	double speed = 0.5;

	if (map->player.move_down)
	{
		if (map->player.player_y < 15)
			map->player.player_y += speed;
	}
	if (map->player.move_up)
	{
		if (map->player.player_y > 0)
			map->player.player_y -= speed;
	}
	if (map->player.move_left)
	{
		if (map->player.player_x > 0)
			map->player.player_x -= speed;
	}
	if (map->player.move_right)
	{
		if (map->player.player_x < 35)
			map->player.player_x += speed;
	}
	return (0);
}

int	loop_hook(t_map_data *map)
{
	update_player_pos(map);
	put_map(map);
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
