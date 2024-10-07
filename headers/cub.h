/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:48:56 by fberthou          #+#    #+#             */
/*   Updated: 2024/10/07 10:12:05 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

	# include "mlx.h"
	# include "mlx_int.h"
	# include "libft.h"
	# include "struct.h"
	# include <stdio.h>
	# include <stdlib.h>
	# include <string.h>
	# include <math.h>

	#define	M_SPEED		3
	#define	R_SPEED		0.05
	#define WIN_WIDTH	1300//2300
	#define WIN_HEIGHT	750//1500
    #define CELL_SIZE	30
    #define EAST_ANGLE  (2 * PI)
    #define WEST_ANGLE  (PI)
    #define NORTH_ANGLE (PI/2)
    #define SOUTH_ANGLE (3*PI)/2

	/*==== main/utils.c ====*/
	void	ft_perror(char *err_message);
    void    free_console(t_map_data *map);
    void	free_all(t_map_data *map);

	/*==== init_env/init_env.c ====*/
	int		init_env(t_map_data *map);

	/*==== init_env/hook.c ====*/
    void	hook_management(t_map_data *map);

	#define	MOVE_DOWN(map)	\
			if (map->player.pos_y < 14 * CELL_SIZE - (CELL_SIZE + 11)) \
				map->player.pos_y += M_SPEED

	#define	MOVE_RIGHT(map)	\
		if (map->player.pos_x < ft_strlen(map->map[0]) * CELL_SIZE - (CELL_SIZE + 11)) \
			map->player.pos_x += (double) M_SPEED

	#define	MOVE_UP(map)	\
			if (map->player.pos_y > 0 + CELL_SIZE) \
				map->player.pos_y -= (double) M_SPEED

	#define	MOVE_LEFT(map)	\
		if (map->player.pos_x > 0 + CELL_SIZE) \
			map->player.pos_x -= (double) M_SPEED

    #define INIT_PLAYER(x, y, a)    \
        map->player.dir_x = x; \
        map->player.dir_y = y; \
        map->player.angle = a \


#endif
