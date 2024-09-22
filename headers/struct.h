/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 09:24:49 by fberthou          #+#    #+#             */
/*   Updated: 2024/09/21 17:39:59 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

	typedef struct	s_console
	{
		void			*mlx_ptr;
		void			*win_ptr;
		unsigned int	win_width;
		unsigned int	win_height;
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
		int floor[3];
		int ceiling[3];
    }	t_colors;

    typedef struct	s_img_data
    {
        void    	*img;
        char    	*addr;
        int     	bits_per_pixel;
        int     	line_length;
        int         endian;
        unsigned    img_width;
        unsigned    img_height;
    }   t_img_data;

	typedef struct	s_map_data
	{
		char        **map;
        t_img_data  img;
		t_colors    colors;
		t_console   console;
		t_textures  text_path;
	}	t_map_data ;

#endif
