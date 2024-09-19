/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:47:23 by fberthou          #+#    #+#             */
/*   Updated: 2024/09/19 17:02:10 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_perror(char *err_message)
{
	write(2, "Error\n", 6);
	if (err_message)
		write(2, err_message, ft_strlen(err_message));
	return;
}

void	free_all(t_map_data *map)
{
	if (map->console.mlx_ptr != NULL)
	{
		mlx_destroy_window(map->console.mlx_ptr, map->console.win_ptr);
		mlx_destroy_display(map->console.mlx_ptr);
		free(map->console.mlx_ptr);
		map->console.mlx_ptr = NULL ;
	}
}