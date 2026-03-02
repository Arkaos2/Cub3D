#include "../../includes/cub3d.h"

int	is_wall(t_game *game, int x, int y)
{
	int	map_x;
	int	map_y;

	if (x < 0 || y < 0 || x >= game->width * 32 || y >= game->height * 32)
		return (1);
	map_x = x / 32;
	map_y = y / 32;
	if (map_y >= game->height || map_x >= game->width)
		return (1);
	return (game->map[map_y][map_x] == '1');
}

static double	cast_ray(t_game *game, double ray_angle)
{
	double	x;
	double	y;
	double	dx;
	double	dy;
	double	distance;

	x = game->player_x + 16;
	y = game->player_y + 16;
	dx = cos(ray_angle);
	dy = sin(ray_angle);
	while (!is_wall(game, (int)x, (int)y))
	{
		x += dx * 0.5;
		y += dy * 0.5;
	}
	distance = sqrt((x - (game->player_x + 16)) * (x - (game->player_x + 16))
			+ (y - (game->player_y + 16)) * (y - (game->player_y + 16)));
	distance = distance * cos(ray_angle - game->angle);
	return (distance);
}
static void	draw_wall_slice(t_game *game, int x, double distance)
{
	int		wall_height;
	int		wall_top;
	int		wall_bottom;
	int		y;
	int		color;
	int		screen_height;

	screen_height = game->height * 32;
	if (distance < 1)
		distance = 1;
	wall_height = (int)((32.0 / distance) * 277);
	wall_top = (screen_height / 2) - (wall_height / 2);
	wall_bottom = wall_top + wall_height;
	// Dessiner le plafond
	y = 0;
	while (y < wall_top)
	{
		mlx_pixel_put(game->mlx, game->win, x, y, game->c_color);
		y++;
	}
	// Dessiner le mur (gradient selon la distance)
	color = 0x808080;
	if (distance < 50)
		color = 0xFFFFFF;
	else if (distance < 100)
		color = 0xCCCCCC;
	else if (distance < 150)
		color = 0x999999;
	else if (distance < 200)
		color = 0x666666;
	else
		color = 0x333333;
	while (y < wall_bottom && y < screen_height)
	{
		mlx_pixel_put(game->mlx, game->win, x, y, color);
		y++;
	}
	// Dessiner le sol
	while (y < screen_height)
	{
		mlx_pixel_put(game->mlx, game->win, x, y, game->f_color);
		y++;
	}
}

void	draw_rays(t_game *game)
{
	int		i;
	double	fov;
	double	ray_angle;
	double	angle_step;
	double	distance;
	int		screen_width;

	fov = 1.0472;
	screen_width = game->width * 32;
	i = 0;
	while (i < screen_width)
	{
		angle_step = fov / screen_width;
		ray_angle = game->angle - fov / 2 + i * angle_step;
		distance = cast_ray(game, ray_angle);
		draw_wall_slice(game, i, distance);
		i++;
	}
}
