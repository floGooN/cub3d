/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_game.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:10:20 by florian           #+#    #+#             */
/*   Updated: 2024/10/23 17:39:12 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void    draw_line(t_map_data *map, int end_x, int end_y, int color)
{
    int x = map->player.pos_x + 5;
    int y = map->player.pos_y + 5;
    int dx = (int) fabs((double) end_x - x);
    int dy = (int) fabs((double) end_y - y);
    int sx = (x < end_x) ? 1 : -1;
    int sy = (y < end_y) ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2;
    int e2;

    while (1) {
        // Place un pixel aux coordonnées (x, y)
        mlx_pixel_put(map->console.mlx_ptr, map->console.win_ptr, x, y, color);

        // Si on a atteint le point final (end_x, y1), on s'arrête
        if (x == end_x && y == end_y)
            break;

        // Calcul de l'erreur et ajustement des coordonnées
        e2 = err;
        if (e2 > -dx) { err -= dy; x += sx; }
        if (e2 < dy) { err += dx; y += sy; }
    }
}

void    draw_rays(t_map_data *map)
{
    int end_x, end_y;
	int map_x, map_y;

	map->data_ray.nb_ray = 60; // Nombre de rayons à afficher (par exemple 60 rayons pour une vue en cône)
	map->data_ray.fov = (M_PI / 3) / map->data_ray.nb_ray;  // Incrément d'angle entre chaque rayon (60 degrés de champ de vision)

    for (int i = 0; i < map->data_ray.nb_ray; i++)
    {
        map->data_ray.ray_angle = map->player.angle - (M_PI / 6) + i * map->data_ray.fov; // Angle de chaque rayon
        map->data_ray.ray_dir_x = cos(map->data_ray.ray_angle);  // Direction du rayon en X
        map->data_ray.ray_dir_y = sin(map->data_ray.ray_angle);  // Direction du rayon en Y

        // Position actuelle dans la grille
        int grid_x = (int)map->player.pos_x / CELL_SIZE;
        int grid_y = (int)map->player.pos_y / CELL_SIZE;

        // Distance du rayon à la prochaine ligne verticale et horizontale
        double deltaDistX = fabs(1 / map->data_ray.ray_dir_x);
        double deltaDistY = fabs(1 / map->data_ray.ray_dir_y);

        // Variables pour DDA
        double sideDistX, sideDistY;
        int stepX, stepY;

        // Initialisation des pas et de la distance initiale aux premières lignes verticales/horizontales
        if (map->data_ray.ray_dir_x < 0)
        {
            stepX = -1;
            sideDistX = (map->player.pos_x / CELL_SIZE - grid_x) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (grid_x + 1.0 - map->player.pos_x / CELL_SIZE) * deltaDistX;
        }

        if (map->data_ray.ray_dir_y < 0)
        {
            stepY = -1;
            sideDistY = (map->player.pos_y / CELL_SIZE - grid_y) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (grid_y + 1.0 - map->player.pos_y / CELL_SIZE) * deltaDistY;
        }

        int hit = 0; // Flag pour savoir si le rayon touche un mur
        int side;    // Pour savoir si c'est une collision sur une ligne verticale ou horizontale

        // Algorithme DDA : on avance dans la grille jusqu'à toucher un mur
        while (hit == 0)
        {
            // Choisir si on avance sur l'axe X ou Y en fonction de la distance la plus courte
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                grid_x += stepX;
                side = 0; // Collision sur une ligne verticale
            }
            else
            {
                sideDistY += deltaDistY;
                grid_y += stepY;
                side = 1; // Collision sur une ligne horizontale
            }

            // Vérification de la collision avec un mur
            if (map->map[grid_y][grid_x] == '1')
                hit = 1;
        }

        // Calcul de la distance à laquelle le mur est touché
        double perpWallDist;
        if (side == 0)
            perpWallDist = (grid_x - map->player.pos_x / CELL_SIZE + (1 - stepX) / 2) / map->data_ray.ray_dir_x;
        else
            perpWallDist = (grid_y - map->player.pos_y / CELL_SIZE + (1 - stepY) / 2) / map->data_ray.ray_dir_y;

        // Calcul des coordonnées finales pour dessiner le rayon
        end_x = map->player.pos_x + map->data_ray.ray_dir_x * perpWallDist * CELL_SIZE;
        end_y = map->player.pos_y + map->data_ray.ray_dir_y * perpWallDist * CELL_SIZE;

        // Dessiner la ligne du rayon
        draw_line(map, end_x, end_y, 0x00FF00); // Vert pour la ligne complète du rayon
    }
}


void    draw_player(t_map_data *map)
{
    int     p_color = 0xFF0000;
    double  radius = 5;
    double  center_x = map->player.pos_x + radius;
    double  center_y = map->player.pos_y + radius;

	/* draw player in 2d map */
	for (int y = 0; y < radius * 2; y++){
		for (int x = 0; x < radius * 2; x ++){
			if (sqrt(pow(x - radius, 2) + pow(y - radius, 2)) <= radius)
				mlx_pixel_put(map->console.mlx_ptr, map->console.win_ptr, center_x - (x - radius), center_y - (y - radius), p_color);
		}
	}
    draw_rays(map);
    return ;
}

void	draw_map(t_map_data *map, int color, int start_y, int start_x)
{
    int i;
    int j;

    i = 0;
    j = 0;
    /* draw 2d map */
    while(i < CELL_SIZE)
    {
		mlx_pixel_put(map->console.mlx_ptr, map->console.win_ptr, start_x + i, \
						start_y, color);
        while (j < CELL_SIZE)
        {
			mlx_pixel_put(map->console.mlx_ptr, map->console.win_ptr, \
                            start_x + i, start_y + j, color);
            j++;
        }
        j = 0;
        i++;
    }
	return ;
}

void	put_map(t_map_data *map)
{
	int	color;
    int y;
    int x;

    y = 0;
    x = 0;
    while (y < 15) // y < map height
    {
        while (x < 35) // x < map width
        {
            if (map->map[y][x] == '1')
                color = 0xFFFFFF; // white for walls
            else
                color = 0x000000; // black for empty spaces
            draw_map(map, color, y * CELL_SIZE, x * CELL_SIZE);
            x++;
        }
        x = 0;
        y++;
    }
    draw_player(map);
    return ;
}

int	update_player_pos(t_map_data *map)
{
	if (map->player.move_down)
        MOVE_DOWN(map);
	if (map->player.move_up)
        MOVE_UP(map);
	if (map->player.move_left)
        MOVE_LEFT(map);
	if (map->player.move_right)
        MOVE_RIGHT(map);
    if (map->player.rotate_left)
        map->player.angle -= R_SPEED;
    if (map->player.rotate_right)
        map->player.angle += R_SPEED;
    if (map->player.rotate_left || map->player.rotate_right)
    {
        map->player.dir_x = cos(map->player.angle);
        map->player.dir_y = sin(map->player.angle);
    }
	return (0);
}

int	loop_hook(t_map_data *map)
{
	if (map->player.move_down || map->player.move_up || \
		map->player.move_left || map->player.move_right || \
		map->player.rotate_left || map->player.rotate_right)
	{
		update_player_pos(map);
		put_map(map);
	}
	return (0);
}

void    display_game(t_map_data *map)
{
    put_map(map);
	mlx_loop_hook(map->console.mlx_ptr, loop_hook, map);
	mlx_loop(map->console.mlx_ptr);
    return ;
}
