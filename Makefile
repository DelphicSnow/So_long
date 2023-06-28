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
SRCS = src/main.c src/check.c src/error.c src/sprites.c src/move.c src/free.c src/map_parsing.c
SRCS_GNL = lib/gnl/get_next_line.c  lib/gnl/get_next_line_utils.c 
CFLAGS += -Wall -Wextra -Werror -g

MLX = lib/mlx
PRINT_F = lib/ft_printf
INC = -I $(MLX) -I $(PRINT_F)
LFLAGS = -L $(MLX) -L $(PRINT_F) -lmlx -lXext -lX11 -lftprintf

OBJ_DIR = obj/
OBJS = $(addprefix $(OBJ_DIR), $(notdir $(SRCS:.c=.o)))
OBJS_GNL = $(addprefix $(OBJ_DIR), $(notdir $(SRCS_GNL:.c=.o)))
# $(SRCS:.c=.o): substitutes the .c extension with .o for each file name in the SRCS variable.
# result  will be src/main.o ...
# $(notdir $(SRCS:.c=.o)): applies the notdir function to the result of $(SRCS:.c=.o),
# which removes the directory part from each file name.
#The result will be main.o ...
# $(addprefix $(OBJ_DIR), $(notdir $(SRCS:.c=.o))): adds the OBJ_DIR prefix to each file name generated from the previous step.
# the final result will be obj/main.o ...
all: library $(NAME)

library:
	@make -sC $(PRINT_F)
	@make -sC $(MLX)

$(NAME): $(OBJS) $(OBJS_GNL)
	cc $(OBJS) $(OBJS_GNL) $(LFLAGS) -o $(NAME)

$(OBJ_DIR)%.o: src/%.c
	@mkdir -p $(OBJ_DIR)
	cc $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR)%.o: lib/gnl/%.c
	@mkdir -p $(OBJ_DIR)
	cc $(CFLAGS) $(INC) -c $< -o $@

clean:
	make clean -C $(PRINT_F)
	make clean -C $(MLX)
	rm -rf $(OBJ_DIR)

fclean:	clean
	rm -f $(NAME)
	make fclean -C $(PRINT_F)
	
re:	fclean all

.PHONY: all library clean fclean re
