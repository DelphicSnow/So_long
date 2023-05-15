/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 18:29:57 by tkajanek          #+#    #+#             */
/*   Updated: 2023/05/15 16:57:43 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	init_art (t_art *art)
{
	art->img_hight = 0;
	art->img_width = 0;
	art->wall = NULL;
	art->floor = NULL;
	art->exit = NULL;
	art->collectible = NULL;
	art->mlx_ptr = NULL;
	art->win_ptr = NULL;
}

void	init_map_data (t_map_data *map, int fd)
{
	map->w = 0;
	map->h = 0;
	map->exit = 0;
	map->collectible = 0;
	map->player = 0;
	map->position[0] = 0;
	map->position[1] = 0;
	map->matrix = NULL;
	map->extracted_map = ft_strdup("");
	map->line = get_next_line(fd);
	map->art = NULL;
}

//kontrola
void	print_matrix(char** matrix)
{
    for (int i = 0; matrix[i] != NULL; i++)
	{
		ft_printf("%s\n", matrix[i]);
    }
}//kontrola

void	parse_map(char *map_file, t_map_data *map)
{
	int	fd;
	
	fd = open(map_file, O_RDONLY);
	if (fd == -1)
	 	ft_error(0, NULL, NULL);
	init_map_data(map, fd);
	while (map->line != NULL)
	{
		map->extracted_map = ft_strjoin_gnl(map->extracted_map, map->line);
		free(map->line);
		map->line = get_next_line (fd);
		map->h++;
	}
	map->matrix = ft_split(map->extracted_map, '\n');
	free(map->extracted_map);
	free(map->line);
	if (map->matrix[0])
		map->w = ft_strlen(map->matrix[0]);
	check_symbols(map->matrix, map);
	check_rectangularity(map->matrix);
	check_prison(map->matrix, map->h, map->w);
	check_valid_path(map->matrix, map);
	close(fd);
}

/*
void	init_art(t_art *art)
{

	init_sprite	exit;
	init_sprite	collectible;
	void	*mlx_ptr;
}*/
int	main(int argc, char **argv)
{
	t_map_data	map;
	t_art	art;
	
	error_arguments(argc, argv);
	parse_map(argv[1], &map);
	//print_matrix(map.matrix);
	//free_shiats(map.matrix, NULL);
	//exit(0);
	init_art(&art);
	map.art = &art;
	art.mlx_ptr = mlx_init();//pointery jsou mozna allokovat->free
	art.win_ptr = mlx_new_window(art.mlx_ptr, map.w * 32, map.h * 32, "game");
	init_idle_objects(&art);
	graphics(&map);	
}