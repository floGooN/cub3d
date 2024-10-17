/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 09:24:49 by fberthou          #+#    #+#             */
/*   Updated: 2024/09/25 08:23:47 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

	typedef enum	e_playdir
	{
		NORTH,
		SOUTH,
		EAST,
		WEST
	}   t_playdir;

	typedef struct	s_player
	{
		t_playdir   dir;
    	double		dir_x;
		double		dir_y;
        double      pos_x;
        double      pos_y;
        double      angle;
		bool		move_up;
		bool		move_down;
		bool		move_left;
		bool		move_right;
		bool		rotate_left;
		bool		rotate_right;
	}	t_player;

	typedef struct	s_texture_path
	{
		char	*n_text;
		char	*s_text;
		char	*e_text;
		char	*w_text;
		int		floor[3];
		int		ceiling[3];
    }	t_textures;

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

    typedef struct  s_data_ray
    {
        int     nb_ray;
        double  fov; // == (PI / 3) / nb_ray == angle field of view
        double  ray_angle;
        double  ray_dir_x;
        double  ray_dir_y;
        double  max_ray_length; // == ft_strlen(map[0])
        bool	hit_wall;


    }   t_data_ray;

    typedef struct	s_console
	{
		void	*mlx_ptr;
		void	*win_ptr;
		int		win_width;
		int		win_height;
	}	t_console;

	typedef struct	s_map_data
	{
		char        **map;
		t_img_data  img;
		t_console   console;
		t_player	player;
		t_textures  text_path;
		t_data_ray	data_ray;
	}	t_map_data ;

#endif
