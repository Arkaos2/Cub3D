#include "../../includes/cub3d.h"

static int	get_wall_color(double distance)
{
	if (distance < 50)
		return (0xFFFFFF);
	else if (distance < 100)
		return (0xCCCCCC);
	else if (distance < 150)
		return (0x999999);
	else if (distance < 200)
		return (0x666666);
	return (0x333333);
}

static void	draw_ceiling(t_game *game, int x, int wall_top)
{
	int	y;

	y = 0;
	while (y < wall_top)
	{
		mlx_pixel_put(game->mlx, game->win, x, y, game->c_color);
		y++;
	}
}

static void	draw_floor(t_game *game, int x, int y)
{
	int	screen_height;

	screen_height = game->height * 32;
	while (y < screen_height)
	{
		mlx_pixel_put(game->mlx, game->win, x, y, game->f_color);
		y++;
	}
}

void	draw_wall_slice_2d(t_game *game, int x, double distance)
{
	int	wall_height;
	int	wall_top;
	int	wall_bottom;
	int	y;
	int	screen_height;

	screen_height = game->height * 32;
	if (distance < 1)
		distance = 1;
	wall_height = (int)((32.0 / distance) * 277);
	wall_top = (screen_height / 2) - (wall_height / 2);
	wall_bottom = wall_top + wall_height;
	draw_ceiling(game, x, wall_top);
	y = wall_top;
	while (y < wall_bottom && y < screen_height)
	{
		mlx_pixel_put(game->mlx, game->win, x, y,
			get_wall_color(distance));
		y++;
	}
	draw_floor(game, x, y);
}
