/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 16:53:46 by saibelab          #+#    #+#             */
/*   Updated: 2026/03/04 16:53:46 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	draw_rays(t_game *game)
{
	int		i;
	double	fov;
	double	ray_angle;
	double	distance;

	fov = 1.0472;
	i = 0;
	while (i < game->width * 32)
	{
		ray_angle = game->angle - fov / 2
			+ i * (fov / (game->width * 32));
		distance = cast_ray(game, ray_angle);
		draw_wall_slice_2d(game, i, distance);
		i++;
	}
}

void	draw_player_direction(t_game *game)
{
	double	x;
	double	y;
	double	dx;
	double	dy;

	x = game->player_x + 16;
	y = game->player_y + 16;
	dx = cos(game->angle);
	dy = sin(game->angle);
	while (!is_wall(game, (int)x, (int)y))
	{
		x += dx;
		y += dy;
	}
	mlx_pixel_put(game->mlx, game->win, (int)x, (int)y, 0xFF0000);
	mlx_pixel_put(game->mlx, game->win, (int)x + 1, (int)y, 0xFF0000);
	mlx_pixel_put(game->mlx, game->win, (int)x - 1, (int)y, 0xFF0000);
	mlx_pixel_put(game->mlx, game->win, (int)x, (int)y + 1, 0xFF0000);
	mlx_pixel_put(game->mlx, game->win, (int)x, (int)y - 1, 0xFF0000);
}
