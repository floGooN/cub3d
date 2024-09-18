# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/03 11:07:17 by fberthou          #+#    #+#              #
#    Updated: 2024/09/18 11:27:34 by fberthou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# --- SET COLORS --- #
RESET_COLOR	= \033[0m
GREEN		= \033[32m
YELLOW		= \033[33m

# --- PROG NAME --- #
NAME		= cub3d
LIBFT		= $(LIBFT_PATH)/libft.a
MLX			= $(MLX_PATH)/libmlx_Linux.a


# --- SET PATHS --- #
#PROJECT#
HDR_PATH				= headers
SRC_PATH				= sources
MAIN_PATH				= $(SRC_PATH)/main
PARSING_PATH			= $(SRC_PATH)/parsing
INIT_WIN_PATH			= $(SRC_PATH)/init_win

#LIBFT#
LIBFT_PATH				= libft
LIBFT_HDR_PATH			= $(LIBFT_PATH)/hdr
MLX_HDR_PATH			= minilibx-linux

#MLX#
MLX_PATH				= minilibx-linux

#TEMPORARY FILES#
BUILD_PATH				= .build


# --- COMPILATION FLAGS --- #
LIB_FLAGS	=	-I$(LIBFT_HDR_PATH) -I$(MLX_HDR_PATH)
MLX_FLAGS	=	-lXext -lX11 -lm -lz -Lminilibx-linux -lmlx_Linux -Lmlx_linux -L/usr/lib -Imlx_linux
COMPFLAGS	=	-I$(HDR_PATH) $(LIB_FLAGS) -Wall -Wextra -Werror -g

SRC		=	$(MAIN_PATH)/main.c

### ---- TEMPORARY FILES ---- ###
OBJ	= $(SRC:$(SRC_PATH)/%.c=$(BUILD_PATH)/%.o)

### --- CALL --- ###
default	: all
all		: $(LIBFT) $(MLX) $(NAME)

### --- CUB3D --- ###
$(NAME)	: $(OBJ) $(LIBFT) $(MLX)
	$(CC) $^ -o $@ $(MLX_FLAGS)
	@echo "$(GREEN)-- cub3d ready --$(RESET_COLOR)"

### --- LIBRAIRIES --- ###
$(LIBFT)	: FORCE
	@$(MAKE) -C $(LIBFT_PATH)/ all

$(MLX)		: FORCE
	@$(MAKE) -C $(MLX_PATH)/ all

#######     OBJECTS    #######
$(BUILD_PATH)/%.o : $(SRC_PATH)/%.c Makefile
	@mkdir -p $(dir $@)
	$(CC) $(COMPFLAGS) -c $< -o $@

FORCE	:

### --- CLEAN MANAGEMENT --- ###
clean	:
	@rm -rf $(BUILD_PATH)
	$(MAKE) -C $(LIBFT_PATH) clean
	$(MAKE) -C $(MLX_PATH) clean
	@echo "$(YELLOW)-- removed temporary files --$(RESET_COLOR)"

fclean	:
	$(MAKE) -C $(MLX_PATH) clean
	$(MAKE) -C $(LIBFT_PATH) fclean
	@rm -rf $(BUILD_PATH) $(NAME)
	@echo "$(YELLOW)-- removed cub3d --$(RESET_COLOR)"

 re		: fclean all

.PHONY	: clean fclean re FORCE default all