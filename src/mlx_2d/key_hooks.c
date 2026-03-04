/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 16:53:40 by saibelab          #+#    #+#             */
/*   Updated: 2026/03/04 16:53:40 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	handle_movement(int keycode, t_game *game)
{
	if (move_player(keycode, game))
	{
		render_3d(game);
	}
}

int	handle_key(int keycode, t_game *game)
{
	double	rot_speed;

	rot_speed = 0.1;
	if (keycode == 65307)
		cleanup(game);
	if (keycode == 65363)
	{
		game->angle -= rot_speed;
		render_3d(game);
	}
	else if (keycode == 65361)
	{
		game->angle += rot_speed;
		render_3d(game);
	}
	else if (keycode == 119 || keycode == 115
		|| keycode == 97 || keycode == 100)
		handle_movement(keycode, game);
	return (0);
}

int	can_move(t_game *game, int n_px, int n_py)
{
	int	s;
	int	z;

	s = 16;
	z = 8;
	if (n_px < 0 || n_py < 0 || n_px + 32 > game->width * 32
		|| n_py + 32 > game->height * 32)
		return (0);
	if (game->map[(n_py + z) / 32][(n_px + z) / 32] == '1')
		return (0);
	if (game->map[(n_py + z) / 32][(n_px + z + s - 1) / 32] == '1')
		return (0);
	if (game->map[(n_py + z + s - 1) / 32][(n_px + z) / 32] == '1')
		return (0);
	if (game->map[(n_py + z + s - 1) / 32][(n_px + z + s - 1) / 32] == '1')
		return (0);
	return (1);
}

static void	get_move_delta(int keycode, t_game *game, int *dx, int *dy)
{
	double	move_speed;

	move_speed = 4.0;
	*dx = 0;
	*dy = 0;
	if (keycode == 119)
		1 && (*dx = (int)(cos(game->angle) * move_speed),
		*dy = (int)(sin(game->angle) * move_speed));
	else if (keycode == 115)
		1 && (*dx = (int)(-cos(game->angle) * move_speed),
		*dy = (int)(-sin(game->angle) * move_speed));
	else if (keycode == 100)
		1 && (*dx = (int)(cos(game->angle - M_PI / 2) * move_speed),
		*dy = (int)(sin(game->angle - M_PI / 2) * move_speed));
	else if (keycode == 97)
		1 && (*dx = (int)(cos(game->angle + M_PI / 2) * move_speed),
		*dy = (int)(sin(game->angle + M_PI / 2) * move_speed));
}

int	move_player(int keycode, t_game *game)
{
	int	dx;
	int	dy;
	int	moved;

	moved = 0;
	get_move_delta(keycode, game, &dx, &dy);
	if (can_move(game, game->player_x + dx, game->player_y + dy))
	{
		game->player_x += dx;
		game->player_y += dy;
		moved = 1;
	}
	else if (can_move(game, game->player_x + dx, game->player_y))
	{
		game->player_x += dx;
		moved = 1;
	}
	else if (can_move(game, game->player_x, game->player_y + dy))
	{
		game->player_y += dy;
		moved = 1;
	}
	if (moved)
		1 && (game->x = game->player_x / 32, game->y = game->player_y / 32);
	return (moved);
}
