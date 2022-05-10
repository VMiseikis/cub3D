# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/22 14:37:39 by vmiseiki          #+#    #+#              #
#    Updated: 2022/05/09 18:16:43 by vmiseiki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Color codes
RESET	= \033[0m
GREEN	= \033[32m
YELLOW	= \033[33m
BLUE	= \033[34m

# Name of the program
NAME = cub3D

# Compilation flags
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror

# Frameworks
OGL = -framework OpenGL -framework AppKit

# Folders
SRC_DIR = ./src/
MLX_DIR = ./mlx/
INC_DIR = ./include/
LIB_DIR = ./libraries/
UTILS_DIR = ./utils/
INPUT_DIR = ./input/
LIBFT_DIR = ./libft/

# Source files
SRC = $(SRC_DIR)*.c
UTI = $(SRC_DIR)$(UTILS_DIR)*c
INP = $(SRC_DIR)$(INPUT_DIR)*c
INC = $(INC_DIR)*.h
LIB = $(LIB_DIR)*.a


# Compilation rules
all: lib_make $(NAME)

$(NAME): $(SRC) $(UTI) $(INP)
	@echo "$(YELLOW)----- Compiling. Please Wait! -----$(RESET)"
	@$(CC) $(CFLAGS) $(OGL) $(LIB) -o $@ $^
	@echo "$(GREEN)----- Compilation completed!  -----$(RESET)"

lib_make:
	@$(MAKE) -C $(MLX_DIR)
	@cp -f $(MLX_DIR)libmlx.a $(LIB_DIR)
	@$(MAKE) -C $(LIBFT_DIR)
	@cp -f $(LIBFT_DIR)libft.a $(LIB_DIR)
	
clean:
	@rm -f $(NAME)

fclean:
	@rm -f $(NAME)
	@rm -f *.o

re: fclean all

.PHONY: all clean fclean re
