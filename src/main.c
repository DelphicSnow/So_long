/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 18:29:57 by tkajanek          #+#    #+#             */
/*   Updated: 2023/05/19 18:12:48 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	init_art(t_art *art)
{
	art->img_height = 0;
	art->img_width = 0;
	art->wall = NULL;
	art->floor = NULL;
	art->exit = NULL;
	art->collectible = NULL;
	art->mlx_ptr = NULL;
	art->win_ptr = NULL;
}

void	init_map_data(t_map_data *map, int fd)
{
	map->w = 0;
	map->h = 0;
	map->exit = 0;
	map->collectible = 0;
	map->collectible_collected = 0;
	map->player = 0;
	map->position[0] = 0;
	map->position[1] = 0;
	map->steps = 0;
	map->matrix = NULL;
	map->extracted_map = ft_strdup("");
	map->line = get_next_line(fd);
	map->art = NULL;
}

void	init_flood(t_flood *flood)
{
	flood->matrix_copy = NULL;
	flood->collectible = 0;
	flood->exit = false;
}

void	init_objects(t_art	*art)
{
	art->wall = mlx_xpm_file_to_image(art->mlx_ptr, "./sprites/wall.xpm",
			&art->img_width, &art->img_height);
	art->floor = mlx_xpm_file_to_image(art->mlx_ptr, "./sprites/floor.xpm",
			&art->img_width, &art->img_height);
	art->exit = mlx_xpm_file_to_image(art->mlx_ptr, "./sprites/exit.xpm",
			&art->img_width, &art->img_height);
	art->collectible = mlx_xpm_file_to_image(art->mlx_ptr, "./sprites/col.xpm",
			&art->img_width, &art->img_height);
	art->player = mlx_xpm_file_to_image(art->mlx_ptr, "./sprites/player.xpm",
			&art->img_width, &art->img_height);
}

int	main(int argc, char **argv)
{
	t_map_data	map;
	t_art		art;

	error_arguments(argc, argv);
	parse_map(argv[1], &map);
	init_art(&art);
	map.art = &art;
	art.mlx_ptr = mlx_init();
	art.win_ptr = mlx_new_window(art.mlx_ptr, map.w * 50, map.h * 50, "game");
	init_objects(&art);
	graphics(&map);
}
