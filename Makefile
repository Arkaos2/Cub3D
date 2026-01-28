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

NAME			= cub3d
CC				= cc
CFLAGS			= -Wall -Wextra -Werror -g3 -Ilibft/includes -Iincludes
LDFLAGS			= -lreadline

SRCS			= src/main.c \
			src/gc.c \
			src/gc_utils.c \
			src/parsing/check_arg.c \
			src/parsing/check_map.c \
			src/parsing/check_valid_map.c


OBJS			= $(SRCS:.c=.o)

LIBFT_PATH		=	libs/libft
LIBFT			= $(LIBFT_PATH)/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_PATH)

%.o: %.c includes/cub3d.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS) $(BONUS_OBJS)
	@$(MAKE) -C $(LIBFT_PATH) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C  $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all clean fclean re bonus
