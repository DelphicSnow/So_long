/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:30:10 by tkajanek          #+#    #+#             */
/*   Updated: 2023/05/19 18:14:38 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	free_shiats(char **matrix, char **matrix_flood)
{
	int	i;

	i = 0;
	if (matrix != NULL)
	{
		while (matrix[i])
		{
			free(matrix[i]);
			i++;
		}
		free(matrix);
	}
	i = 0;
	if (matrix_flood != NULL)
	{
		while (matrix_flood[i])
		{
			free(matrix_flood[i]);
			i++;
		}
		free(matrix_flood);
	}
}

void	imgs_cide(t_art *art)
{
	mlx_destroy_image(art->mlx_ptr, art->wall);
	mlx_destroy_image(art->mlx_ptr, art->floor);
	mlx_destroy_image(art->mlx_ptr, art->player);
	mlx_destroy_image(art->mlx_ptr, art->collectible);
	mlx_destroy_image(art->mlx_ptr, art->exit);
}

int	suicide(t_map_data *map)
{
	free_shiats(map->matrix, NULL);
	imgs_cide(map->art);
	mlx_destroy_window(map->art->mlx_ptr, map->art->win_ptr);
	mlx_destroy_display(map->art->mlx_ptr);
	free(map->art->mlx_ptr);
	exit (EXIT_SUCCESS);
}

void	win_check(t_map_data *map)
{
	if (map->collectible_collected == map->collectible)
	{
		ft_printf("Congratz, you finished the game with %d steps!\n",
			map->steps + 1);
		suicide(map);
	}
}
