/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 09:20:33 by fberthou          #+#    #+#             */
/*   Updated: 2024/09/22 19:43:44 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	put_square(t_map_data *map, int color, int y, int x)
{
	for (int i = 0; i < map->cell_height; i++)
	{
		mlx_pixel_put(map->console.mlx_ptr, map->console.win_ptr, x * map->cell_width + i, y * map->cell_height, color);
		for (int j = 0; j < map->cell_width; j++){
			mlx_pixel_put(map->console.mlx_ptr, map->console.win_ptr, x * map->cell_width + i, y * map->cell_height + j, color);
		}
	}
	return ;
}

void	put_map(t_map_data *map, char r_map[15][35])
{
	int	color;
	
	for (int y = 0; y < 15 ; y++)
	{
		for (int x = 0; x < 35; x++)
		{
			if (r_map[y][x] == '1')
				color = 0xFFFFFF; // Blanc pour les murs
			else
				color = 0x000000; // Noir pour les espaces vides
			put_square(map, color, y, x);
		}
	}
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

int	init_env(t_map_data *map, char r_map[15][35])
{
    map->console.win_width = WIN_WIDTH;
    map->console.win_height = WIN_HEIGHT;
	map->cell_width = 10;
	map->cell_height = 10;
	if (init_console(map, map->console.win_width, map->console.win_height))
		return (1);
	hook_management(map);
	put_map(map, r_map);
	mlx_loop(map->console.mlx_ptr);
	return (0);
}
