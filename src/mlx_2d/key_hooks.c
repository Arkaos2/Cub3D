#include "../../includes/cub3d.h"

static void	handle_movement(int keycode, t_game *game)
{
	if (move_player(keycode, game))
	{
		render_3d(game);
	}
}

static int	handle_key(int keycode, t_game *game)
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
	else if (keycode == 119 || keycode == 115 || keycode == 97 || keycode == 100)
		handle_movement(keycode, game);
	return (0);
}

void	setup_hooks(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, handle_key, game);
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

int	move_player(int keycode, t_game *game)
{
	int	new_px;
	int	new_py;
	double	move_speed;

	1 && (move_speed = 4.0, new_px = game->player_x, new_py = game->player_y);
	if (keycode == 119)
		1 && (new_px += (int)(cos(game->angle) * move_speed),
		new_py += (int)(sin(game->angle) * move_speed));
	else if (keycode == 115)
		1 && (new_px -= (int)(cos(game->angle) * move_speed),
		new_py -= (int)(sin(game->angle) * move_speed));
	else if (keycode == 97)
		1 && (new_px += (int)(cos(game->angle - M_PI / 2) * move_speed),
		new_py += (int)(sin(game->angle - M_PI / 2) * move_speed));
	else if (keycode == 100)
		1 && (new_px += (int)(cos(game->angle + M_PI / 2) * move_speed),
		new_py += (int)(sin(game->angle + M_PI / 2) * move_speed));
	if (can_move(game, new_px, new_py))
	{
		1 && (game->player_x = new_px, game->player_y = new_py);
		1 && (game->x = game->player_x / 32, game->y = game->player_y / 32);
		return (1);
	}
	return (0);
}
