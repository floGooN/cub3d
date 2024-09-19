/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 09:24:49 by fberthou          #+#    #+#             */
/*   Updated: 2024/09/19 14:17:38 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

	typedef struct	s_console
	{
		void			*mlx_ptr;
		void			*win_ptr;
		unsigned int	width;
		unsigned int	height;
	}	t_console;

	typedef struct	s_texture_path
	{
		char	*n_text;
		char	*s_text;
		char	*e_text;
		char	*w_text;
    }	t_textures;

	typedef struct	s_colors
    {
		int	floor[3];
		int	ceiling[3];
    }	t_colors;

	typedef struct	s_map_data
	{
		char        **map;
		t_colors    colors;
		t_console   console;
		t_textures  text_path;
	}	t_map_data ;

#endif