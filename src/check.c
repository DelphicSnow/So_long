/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 20:17:44 by tkajanek          #+#    #+#             */
/*   Updated: 2023/05/13 21:43:35 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	check_prison(char **matrix, int h, int w)
{
	int	i;
	int	j;

	i = 0;
	while (matrix[i])
	{
		j = 0;
		while (matrix[i][j])
			{
				if (i == 0 || j == 0 || i == h - 1 || j == w - 1)
					{
						if (matrix[i][j] != '1')
							ft_error (4, matrix, NULL);
					}
				j++;
			}
		i++;
	}
}

void	flood_fill(t_flood *flood, int y, int x) //prekontrolovat zda x y odpovida
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



char** create_copy_of_matrix_to_fill(char** matrix, int rows)
{
	char **copy;
	int i;
	
    copy = (char**)malloc((rows + 1) * sizeof(char*));
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
void	initialaze_flood(t_flood *flood)
{
	flood->matrix_copy = NULL;
	flood->collectible = 0;
	flood->exit = false;
}
void	check_valid_path(char **matrix, t_map_data *map)
{
	t_flood	flood;

	initialaze_flood(&flood);
	flood.matrix_copy = create_copy_of_matrix_to_fill(matrix, map->h);
	ft_printf("position[0]: %d, position[1]: %d\n", map->position[0], map->position[1]);
	flood_fill(&flood, map->position[0], map->position[1]);
	if (map->collectible != flood.collectible)
		ft_error(5, matrix, flood.matrix_copy);
	if (!flood.exit)
		ft_error(6, matrix, flood.matrix_copy);
	free_shiats(NULL, flood.matrix_copy);
}

void	check_rectangularity(char ** matrix)
{
	int	i;
	int	len;

	len = ft_strlen(matrix[0]);
	i = 1;
	while (matrix[i])
	{
		if (ft_strlen(matrix[i]) != len)
			ft_error(3, matrix, NULL);
		i++;
	}
}


void	check_symbols(char ** matrix, t_map_data *map)
{
	
	int	i;
	int	j;

	i = 0;
	while(matrix[i])
	{
		j = 0;
		while (matrix[i][j])
			{
				if(matrix[i][j] == 'C')
					map->collectible++;
				if(matrix[i][j] == 'E')
					map->exit++;
				if(matrix[i][j] == 'P')
					{
						map->player++;
						map->position[0] = i;
						map->position[1] = j;
					}
				if(!ft_strchr("01CEP", matrix[i][j]))
					ft_error(1, matrix, NULL);
				j++;
			}
		i++;
	}
	if (map->collectible < 1 || map->exit != 1 || map->player != 1)
	ft_error(2, matrix, NULL);
}
int	check_filename (char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 4)
		return (0);
	if (!ft_strncmp(filename + len - 4, ".ber", 4)) 
		return (1);
	return (0);
}

