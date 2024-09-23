/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:48:56 by fberthou          #+#    #+#             */
/*   Updated: 2024/09/23 14:40:31 by fberthou         ###   ########.fr       */
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

	#define WIN_WIDTH 1300//2300
	#define WIN_HEIGHT 750//1500
    #define CELL_WIDTH	30
    #define CELL_HEIGTH	30
	#define	SPEED		3
    #define PI 3.14159265359

	/*==== main/utils.c ====*/
	void	ft_perror(char *err_message);
    void    free_console(t_map_data *map);
    void	free_all(t_map_data *map);

	/*==== init_env/init_env.c ====*/
	int		init_env(t_map_data *map);

	/*==== init_env/hook.c ====*/
    void	hook_management(t_map_data *map);

#endif
