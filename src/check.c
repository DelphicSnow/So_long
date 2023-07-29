/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 20:17:44 by tkajanek          #+#    #+#             */
/*   Updated: 2023/05/19 18:34:04 by tkajanek         ###   ########.fr       */
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

int	check_filename(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 4)
		return (0);
	if (!ft_strncmp(filename + len - 4, ".ber", 4))
		return (1);
	return (0);
}

void	check_rectangularity(char **matrix)
{
	int		i;
	size_t	len;

	len = ft_strlen(matrix[0]);
	i = 1;
	while (matrix[i])
	{
		if (ft_strlen(matrix[i]) != len)
			ft_error(3, matrix, NULL);
		i++;
	}
}

static void	add_player(t_map_data *map, int i, int j)
{
	map->player++;
	map->position[0] = i;
	map->position[1] = j;
}

void	check_symbols(char **matrix, t_map_data *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (matrix[i])
	{
		j = 0;
		while (matrix[i][j])
		{
			if (matrix[i][j] == 'C')
				map->collectible++;
			if (matrix[i][j] == 'E')
				map->exit++;
			if (matrix[i][j] == 'P')
				add_player(map, i, j);
			if (!ft_strchr("01CEP", matrix[i][j]))
				ft_error(1, matrix, NULL);
			j++;
		}
		i++;
	}
	if (map->collectible < 1 || map->exit != 1 || map->player != 1)
		ft_error(2, matrix, NULL);
}
