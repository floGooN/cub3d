/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:48:56 by fberthou          #+#    #+#             */
/*   Updated: 2024/09/19 18:29:19 by fberthou         ###   ########.fr       */
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

	/*==== main/utils.c ====*/
	void	ft_perror(char *err_message);
	void	free_all(t_map_data *map);

	/*==== init_env/init_env.c ====*/
	int		init_env(t_map_data *map);

	
#endif
