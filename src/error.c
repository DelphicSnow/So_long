/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 19:16:57 by tkajanek          #+#    #+#             */
/*   Updated: 2023/05/13 21:43:34 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	free_shiats(char **matrix, char **matrix_flood)
{
	int	i;

	i = 0;
	if (matrix != NULL)
	{
		while(matrix[i])
		{
			free(matrix[i]);
			i++;
		}
		free(matrix);
	}
	i = 0;
	if (matrix_flood != NULL)
	{
		while(matrix_flood[i])
		{
			free(matrix_flood[i]);
			i++;
		}
		free(matrix_flood);
	}
}

void	ft_error(int i, char **matrix, char **matrix_flood)
{
	free_shiats(matrix, matrix_flood);
	if (i == 0)
		ft_printf("ERROR\nThe map file couldn't be opened.\n");
	else if (i == 1)
		ft_printf("ERROR\nInvalid characters detected! Allowed characters are O, 1, C, E, P.\n");
	else if (i == 2)
		ft_printf("ERROR\nThe map must contain 1 exit, at least 1 collectible, and 1 starting position to be valid.\n");
	else if (i == 3)
		ft_printf("ERROR\nThe map doesn't have rectangular shape.\n");
	else if (i == 4)
		ft_printf("ERROR\nThe map is not surrounded by walls.\n");
	else if (i == 5)
		ft_printf("ERROR\nIt is impossible to reach all the collectibles in the map. The path is not valid.\n");
	else if (i == 6)
		ft_printf("ERROR\nIt is not possible to reach the exit. The path is not valid.\n");
	exit(EXIT_FAILURE);
}

void	error_arguments (int argc, char **argv)
{
	if (argc == 1)
	{
		ft_printf("ERROR\nToo few arguments. You need to input a map file.\nUsage: ./%s <map_file>.ber\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	if (argc > 2)
	{
	ft_printf("Only the first argument will be taken into an account\n");
	}
	if(!check_filename(argv[1]))
		{
			ft_printf("ERROR\nMap file must have .ber extension.\n");
			exit(EXIT_FAILURE);
		}
}
