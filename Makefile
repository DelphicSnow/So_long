# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/01 17:53:14 by tkajanek          #+#    #+#              #
#    Updated: 2023/05/15 16:58:51 by tkajanek         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
SRCS = src/main.c src/check.c src/error.c src/sprites.c
SRCS_GNL = lib/gnl/get_next_line.c  lib/gnl/get_next_line_utils.c 
CFLAGS += -Wall -Wextra -Werror -g

MLX = lib/mlx
PRINT_F = lib/ft_printf
INC = -I $(MLX) -I $(PRINT_F)
LFLAGS = -L $(MLX) -L $(PRINT_F) -lmlx -lXext -lX11 -lftprintf


all: library $(NAME)

library:
	make -sC $(PRINT_F)
	make -sC $(MLX)

$(NAME): 
	cc $(INC) -o $(NAME) $(SRCS) $(SRCS_GNL) $(LFLAGS)

clean:
	make clean -C $(PRINT_F)
	make clean -C $(MLX) 

fclean:	clean
	rm -f $(NAME)
	make fclean -C $(PRINT_F)
	
re:	fclean all
