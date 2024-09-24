/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_game.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:10:20 by florian           #+#    #+#             */
/*   Updated: 2024/09/24 16:44:59 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void    draw_line(t_map_data *map, int end_x, int end_y, int color)
{
    int x = map->player.pos_x + 5;
    int y = map->player.pos_y + 5;
    int dx = abs(end_x - x);
    int dy = abs(end_y - y);
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
    int ray_count = 60;  // Nombre de rayons à afficher (par exemple 100 rayons pour une vue en cône)
    double ray_angle_increment = (M_PI / 3) / ray_count; // Incrément d'angle entre chaque rayon (60 degrés de champ de vision)
    double ray_angle;
    double ray_x;
    double ray_y;
    int end_x, end_y;

    // Dessin de chaque rayon
    for (int i = 0; i < ray_count; i++)
    {
        ray_angle = map->player.angle - (M_PI / 6) + i * ray_angle_increment; // Angle de chaque rayon
        ray_x = cos(ray_angle);  // Calcul de la direction en X
        ray_y = sin(ray_angle);  // Calcul de la direction en Y

        // On "projette" le rayon jusqu'à rencontrer un mur ou une limite
        double distance = 0;
        int hit_wall = 0;
        while (hit_wall == 0 && distance < 50) // Limite de distance pour éviter une boucle infinie
        {
            distance += 0.1; // Avancer de petits pas pour tester la collision
            end_x = (int)(map->player.pos_x + ray_x * distance * CELL_SIZE);
            end_y = (int)(map->player.pos_y + ray_y * distance * CELL_SIZE);

            // On vérifie si le rayon touche un mur
            int map_x = end_x / CELL_SIZE;
            int map_y = end_y / CELL_SIZE;
            if (map->map[map_y][map_x] == '1')
                hit_wall = 1;

            // Afficher le rayon si pas encore de collision
            if (!hit_wall)
                mlx_pixel_put(map->console.mlx_ptr, map->console.win_ptr, end_x, end_y, 0x00FF00); // Vert pour le rayon
        }

        // Une fois que le rayon touche un mur, on dessine une ligne complète pour ce rayon
        draw_line(map, end_x, end_y, 0x00FF00); // Vert pour la ligne complète du rayon
    }
}

void    put_player(t_map_data *map)
{
    int     p_color     = 0xFF0000;
    double  radius   = 5;
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
    while (y < 15)
    {
        while (x < 35)
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
    put_player(map);
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
