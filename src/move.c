/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 17:58:55 by tkajanek          #+#    #+#             */
/*   Updated: 2023/07/22 16:05:50 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	render_up(t_map_data *map)
{
	int		coor_x;
	int		coor_y;

	coor_x = map->position[1];
	coor_y = map->position[0];
	if (map->matrix[coor_y - 1][coor_x] != '1')
	{
		if (!(map->matrix[coor_y - 1][coor_x] == 'E'))
		{
			if (map->matrix[coor_y - 1][coor_x] == 'C')
				map->collectible_collected ++;
			map->matrix[coor_y - 1][coor_x] = 'P';
			map->matrix[coor_y][coor_x] = '0';
			map->steps += 1;
			map->position[0] -= 1;
		}
		else
			win_check(map);
	}
}

void	render_down(t_map_data *map)
{
	int		coor_x;
	int		coor_y;

	coor_x = map->position[1];
	coor_y = map->position[0];
	if (map->matrix[coor_y + 1][coor_x] != '1')
	{
		if (!(map->matrix[coor_y + 1][coor_x] == 'E'))
		{
			if (map->matrix[coor_y + 1][coor_x] == 'C')
				map->collectible_collected ++;
			map->matrix[coor_y + 1][coor_x] = 'P';
			map->matrix[coor_y][coor_x] = '0';
			map->steps += 1;
			map->position[0] += 1;
		}
		else
			win_check(map);
	}
}

void	render_right(t_map_data *map)
{
	int		coor_x;
	int		coor_y;

	coor_x = map->position[1];
	coor_y = map->position[0];
	if (map->matrix[coor_y][coor_x + 1] != '1')
	{
		if (!(map->matrix[coor_y][coor_x + 1] == 'E'))
		{
			if (map->matrix[coor_y][coor_x + 1] == 'C')
				map->collectible_collected ++;
			map->matrix[coor_y][coor_x + 1] = 'P';
			map->matrix[coor_y][coor_x] = '0';
			map->steps += 1;
			map->position[1] += 1;
		}
		else
			win_check(map);
	}
}

void	render_left(t_map_data *map)
{
	int		coor_x;
	int		coor_y;

	coor_x = map->position[1];
	coor_y = map->position[0];
	if (map->matrix[coor_y][coor_x - 1] != '1')
	{
		if (!(map->matrix[coor_y][coor_x - 1] == 'E'))
		{
			if (map->matrix[coor_y][coor_x - 1] == 'C')
				map->collectible_collected ++;
			map->matrix[coor_y][coor_x - 1] = 'P';
			map->matrix[coor_y][coor_x] = '0';
			map->steps += 1;
			map->position[1] -= 1;
		}
		else
			win_check(map);
	}
}

int	handle_key(int keycode, t_map_data *map)
{
	if (keycode == XK_Escape)
		suicide(map);
	if (keycode == XK_w)
		render_up(map);
	if (keycode == XK_d)
		render_right(map);
	if (keycode == XK_a)
		render_left(map);
	if (keycode == XK_s)
		render_down(map);
	return (0);
}
