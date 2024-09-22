/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:48:56 by fberthou          #+#    #+#             */
/*   Updated: 2024/09/22 17:43:05 by fberthou         ###   ########.fr       */
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

	#define WIN_WIDTH 2300
	#define WIN_HEIGHT 1500
    #define PI 3.14159265359

	/*==== main/utils.c ====*/
	void	ft_perror(char *err_message);
    void    free_console(t_map_data *map);
    void	free_all(t_map_data *map);

	/*==== init_env/init_env.c ====*/
	int		init_env(t_map_data *map, char r_map[15][35]);

	/*==== init_env/hook.c ====*/
    void	hook_management(t_map_data *map);

#endif
