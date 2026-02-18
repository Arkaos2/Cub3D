#include "cub3d.h"

static void	cleanup(t_game *game)
{
	if (game->img_wall)
		mlx_destroy_image(game->mlx, game->img_wall);
	if (game->img_floor)
		mlx_destroy_image(game->mlx, game->img_floor);
	if (game->img_player)
		mlx_destroy_image(game->mlx, game->img_player);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
		mlx_destroy_display(game->mlx);
	free(game->mlx);
	gc_destroy(game->gc);
	exit(0);
}

static int	can_move(t_game *game, int n_px, int n_py)
{
	int	s;
	int	z;

	s = 24;
	z = 4;
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

static int	move_player(int keycode, t_game *game)
{
	int	new_px;
	int	new_py;

	new_px = game->player_x;
	new_py = game->player_y;
	if (keycode == 119)
		new_py -= 4;
	else if (keycode == 115)
		new_py += 4;
	else if (keycode == 97)
		new_px -= 4;
	else if (keycode == 100)
		new_px += 4;
	if (can_move(game, new_px, new_py))
	{
		game->player_x = new_px;
		game->player_y = new_py;
		game->x = game->player_x / 32;
		game->y = game->player_y / 32;
		return (1);
	}
	return (0);
}

static void	handle_movement(int keycode, t_game *game)
{
	if (move_player(keycode, game))
	{
		mlx_put_image_to_window(game->mlx, game->win,
			game->img_player, game->player_x, game->player_y);
	}
}

static int	handle_key(int keycode, t_game *game)
{

	if (keycode == 65307)
		cleanup(game);
	if (keycode == 119 || keycode == 115 || keycode == 97 || keycode == 100)
		handle_movement(keycode, game);;
	return (0);
}

static void	setup_hooks(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, handle_key, game);
}


static void	load_sprites(t_game *game)
{
	int	w;
	int	h;

	game->img_player = mlx_xpm_file_to_image(game->mlx, "texture/p.xpm", &w, &h);
	game->img_wall = mlx_xpm_file_to_image(game->mlx, "texture/1.xpm", &w, &h);
	game->img_floor = mlx_xpm_file_to_image(game->mlx, "texture/0.xpm", &w, &h);
}

static void	draw_pixel(t_game *game, int x, int y)
{
	if (game->map[y][x] == '1')
		mlx_put_image_to_window(game->mlx, game->win,
			game->img_wall, x * 32, y * 32);
	else
		mlx_put_image_to_window(game->mlx, game->win,
			game->img_floor, x * 32, y * 32);
}
static void	draw_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			draw_pixel(game, x, y);
			x++;
		}
		y++;
	}
}

int	mlx_start(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		gc_destroy(game->gc);
		exit(1);
	}
	game->win = mlx_new_window(game->mlx,
			game->width * 32,
			game->height * 32,
			"cub3D");
	if (!game->win)
	{
		ft_printf("Error\n: impossible de créer la fenêtre\n");
		gc_destroy(game->gc);
		exit(1);
	}
	load_sprites(game);
	setup_hooks(game);
	draw_map(game);
	mlx_put_image_to_window(game->mlx, game->win,
		game->img_player, game->player_x, game->player_y);
	return 1;
}
