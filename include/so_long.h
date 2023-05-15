/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 18:25:31 by tkajanek          #+#    #+#             */
/*   Updated: 2023/05/15 16:57:25 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../lib/mlx/mlx.h"
# include "../lib/ft_printf/ft_printf.h"
# include "../lib/ft_printf/libft/libft.h"
# include "../lib/gnl/get_next_line.h"
# include <stdbool.h>
# include <fcntl.h>



typedef struct s_art
{
	int		img_hight;
	int		img_width;
	void	*wall;
	void	*floor;
	void	*exit;
	void	*collectible;
	void	*mlx_ptr;
	void	*win_ptr;

} t_art;

typedef struct s_map_data
{
	int		w;
	int		h;
	int		exit;
	int		collectible;
	int		player;
	int 	position[2];
	char	**matrix;
	char	*extracted_map;
	char	*line;
	t_art	*art;
}	t_map_data;

typedef struct	s_flood
{
	char		**matrix_copy;
	int			collectible;
	bool		exit;
}				t_flood;


//checkers

int	check_filename (char *filename);
void	check_symbols(char ** matrix, t_map_data *map);
void	check_rectangularity(char ** matrix);
void	check_valid_path(char **matrix, t_map_data *map);
void	check_prison(char **matrix, int h, int w);

void	error_arguments (int argc, char **argv);
void	ft_error(int i, char **matrix, char **matrix_flood);
void	free_shiats(char **matrix, char **matrix_flood);

void init_map_data (t_map_data *map, int fd);
void	parse_map(char *map_file, t_map_data *map);
void	flood_fill(t_flood *flood, int y, int x);
char** create_copy_of_matrix_to_fill(char** matrix, int rows);
void print_matrix(char** matrix); //jen pro kontrolu, pak smazat

void	init_idle_objects(t_art	*art);
void	graphics(t_map_data	*map);
int	render(t_map_data *map);
void	render_background(t_map_data *map);
void	print_img(t_art *art, void *img_ptr, int coor_x, int coor_y);

#endif
