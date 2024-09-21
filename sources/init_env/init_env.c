/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 09:20:33 by fberthou          #+#    #+#             */
/*   Updated: 2024/09/21 17:58:28 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	put_img(t_map_data *map, char r_map[15][35])
{

    // mlx_put_image_to_window(map->console.mlx_ptr, map->console.win_ptr, map->img.img, 5,5);
	// for (int i = 5; i < 500; i++){
	// 	mlx_pixel_put(map->console.mlx_ptr, map->console.win_ptr, i, 5, 0x00FF0000);
	// 	if (i == 49)
	// 	{
	// 		for (int i = 5; i < 50; i++){
	// 			mlx_pixel_put(map->console.mlx_ptr, map->console.win_ptr, 50, i, 0x00FF0000);
	// 			// if (i == 49)
	// 			// {
	// 			// 	for (int i = )
	// 			// }
	// 		}
	// 	}
	// }
}

static int	init_img(t_map_data *map, unsigned width, unsigned height)
{
    map->img.img = mlx_new_image(map->console.mlx_ptr, width, height);
    if (!map->img.img)
        return (free_console(map), 1);
    map->img.addr = mlx_get_data_addr(map->img.img, &map->img.bits_per_pixel, \
									&map->img.line_length, &map->img.endian);
	if (!map->img.addr)
		return (free_all(map), 1);
	return (0);
}

static int	init_console(t_map_data *map, unsigned width, unsigned height)
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
    map->console.win_width = 1366;
    map->console.win_height = 768;
    map->img.img_width = 35;
    map->img.img_height = 15;
	if (init_console(map, map->console.win_width, map->console.win_height))
		return (1);
	if (init_img(map, map->img.img_width, map->img.img_height))
		return (1);
	put_img(map, r_map);
	hook_management(map);
	mlx_loop(map->console.mlx_ptr);
	return (0);
}
