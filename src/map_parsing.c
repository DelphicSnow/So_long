/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:49:46 by tkajanek          #+#    #+#             */
/*   Updated: 2023/05/19 18:27:27 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	flood_fill(t_flood *flood, int y, int x)
{
	if (flood->matrix_copy[y][x] == '1')
		return ;
	if (flood->matrix_copy[y][x] != 'F')
	{
		if (flood->matrix_copy[y][x] == 'C')
			flood->collectible += 1;
		if (flood->matrix_copy[y][x] == 'E')
			flood->exit = true;
		flood->matrix_copy[y][x] = 'F';
		flood_fill(flood, y, x - 1);
		flood_fill(flood, y, x + 1);
		flood_fill(flood, y + 1, x);
		flood_fill(flood, y - 1, x);
	}
	return ;
}

char	**create_copy_of_matrix_to_fill(char **matrix, int rows)
{
	char	**copy;
	int		i;

	copy = (char **)malloc((rows + 1) * sizeof(char *));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < rows)
	{
		copy[i] = ft_strdup(matrix[i]);
		i++;
	}
	copy[rows] = NULL;
	return (copy);
}

void	check_valid_path(char **matrix, t_map_data *map)
{
	t_flood	flood;

	init_flood(&flood);
	flood.matrix_copy = create_copy_of_matrix_to_fill(matrix, map->h);
	flood_fill(&flood, map->position[0], map->position[1]);
	if (map->collectible != flood.collectible)
		ft_error(5, matrix, flood.matrix_copy);
	if (!flood.exit)
		ft_error(6, matrix, flood.matrix_copy);
	free_shiats(NULL, flood.matrix_copy);
}

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
