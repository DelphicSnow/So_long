/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 21:12:45 by tkajanek          #+#    #+#             */
/*   Updated: 2023/05/15 17:25:21 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	print_img(t_art *art, void *img_ptr, int coor_x, int coor_y)
{
	int	i;
	
	i = mlx_put_image_to_window(art->mlx_ptr, art->win_ptr, img_ptr,
		art->img_width * coor_x, art->img_hight * coor_y);
	if (i != 0)
		ft_printf("The image at x = %d, y = %d couldnt be displayed on the window.", coor_x, coor_y);
}

void	render_background(t_map_data *map)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (map->matrix[y] != NULL)
	{
		while (map->matrix[y][x] != '\0')
		{
			if (map->matrix[y][x] == '1')
				print_img(map->art, map->art->wall, x, y);
			if (map->matrix[y][x] == '0')
				print_img(map->art, map->art->floor, x, y);
			x++;
		}
		x = 0;
		y++;
	}
}

int	render(t_map_data *map)
{
	render_background(map);
	//render_other(art);
	return (0);
}

void	graphics(t_map_data	*map)
{
	mlx_loop_hook(map->art->mlx_ptr, &render, map);
	//mlx_key_hook(art->win_ptr, &handle_key, art);
}

void	init_idle_objects(t_art	*art)
{
	
	art->wall = mlx_xpm_file_to_image(art->mlx_ptr, "./sprites/wall.xpm",
			art->img_width, art->img_hight);
	art->floor = mlx_xpm_file_to_image(art->mlx_ptr, "./sprites/floor.xpm",
			art->img_width, art->img_hight);//&art.img_width
	/*art->exit.ptr = mlx_xpm_file_to_image(art->mlx_ptr, "./sprites/exit.xpm",
			&(art->exit.w), &(art->exit.h));
	art->collectible.ptr = mlx_xpm_file_to_image(art->mlx_ptr,
			"./sprites/collectible.xpm",
			&(art->collectible.w), &(art->collectible.h));*/


}