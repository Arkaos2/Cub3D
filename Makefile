# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/10 18:56:32 by saibelab          #+#    #+#              #
#    Updated: 2026/01/05 20:19:27 by saibelab         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= cub3D
LDFLAGS			= -lreadline

SRCS			= src/main.c \
			src/gc.c \
			src/gc_utils.c \
			src/parsing/check_arg.c \
			src/parsing/check_map.c \
			src/parsing/check_valid_map.c \
			src/parsing/utils.c \
			src/parsing/flood_fill.c \
			src/mlx_2d/texture.c


MLX_DIR = libs/minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11

CC				= cc
CFLAGS			= -Wall -Wextra -Werror -g3 -Ilibft/includes -Iincludes -I$(MLX_DIR)
LDFLAGS			= -lreadline


OBJS			= $(SRCS:.c=.o)

LIBFT_PATH		=	libs/libft
LIBFT			= $(LIBFT_PATH)/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) $(MLX_FLAGS) -o $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_PATH)

$(MLX_LIB):
	@$(MAKE) -C $(MLX_DIR)

%.o: %.c includes/cub3d.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS) $(BONUS_OBJS)
	@$(MAKE) -C $(LIBFT_PATH) clean
	@$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C  $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all clean fclean re
.PHONY: all clean fclean re bonus
