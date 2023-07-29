/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 21:12:45 by tkajanek          #+#    #+#             */
/*   Updated: 2023/05/19 18:13:25 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	print_steps(t_map_data *map)
{
	char	*moves;

	moves = ft_itoa(map->steps);
	mlx_string_put(map->art->mlx_ptr, map->art->win_ptr,
		20, 20, 0xFFC0CB, moves);
	free(moves);
}

void	print_img(t_art *art, void *img_ptr, int coor_x, int coor_y)
{
	int	i;

	i = mlx_put_image_to_window(art->mlx_ptr, art->win_ptr, img_ptr,
			art->img_width * coor_x, art->img_height * coor_y);
	if (i != 0)
		ft_printf("The image at x = %d,y = %d couldnt be displayed.",
			coor_x, coor_y);
}

void	render_objects(t_map_data *map)
{
	int		x;
	int		y;

	y = 0;
	while (map->matrix[y] != NULL)
	{	
		x = 0;
		while (map->matrix[y][x] != '\0')
		{
			if (map->matrix[y][x] == '1')
				print_img(map->art, map->art->wall, x, y);
			if (map->matrix[y][x] == '0')
				print_img(map->art, map->art->floor, x, y);
			if (map->matrix[y][x] == 'C')
				print_img(map->art, map->art->collectible, x, y);
			if (map->matrix[y][x] == 'P')
				print_img(map->art, map->art->player, x, y);
			if (map->matrix[y][x] == 'E')
				print_img(map->art, map->art->exit, x, y);
			x++;
		}
		y++;
	}
}

int	render(t_map_data *map)
{
	render_objects(map);
	print_steps(map);
	return (0);
}

void	graphics(t_map_data	*map)
{
	mlx_loop_hook(map->art->mlx_ptr, &render, map);
	mlx_key_hook(map->art->win_ptr, &handle_key, map);
	mlx_hook(map->art->win_ptr, 17, 0, &suicide, map);
	mlx_loop(map->art->mlx_ptr);
}
