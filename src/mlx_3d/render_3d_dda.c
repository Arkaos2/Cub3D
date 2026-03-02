#include "../../includes/cub3d.h"

static void	dda_step(t_ray *ray)
{
	if (ray->sidedist_x < ray->sidedist_y)
	{
		ray->sidedist_x += ray->deltadist_x;
		ray->map_x += ray->step_x;
		ray->side = 0;
	}
	else
	{
		ray->sidedist_y += ray->deltadist_y;
		ray->map_y += ray->step_y;
		ray->side = 1;
	}
}

static void	calculate_perp_dist(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - (game->player_x + 16) / 32.0
				+ (1 - ray->step_x) / 2) / ray->raydir_x;
	else
		ray->perp_wall_dist = (ray->map_y - (game->player_y + 16) / 32.0
				+ (1 - ray->step_y) / 2) / ray->raydir_y;
}

void	perform_dda(t_game *game, t_ray *ray)
{
	while (ray->hit == 0)
	{
		dda_step(ray);
		if (ray->map_x < 0 || ray->map_y < 0
			|| ray->map_x >= game->width || ray->map_y >= game->height)
			break ;
		if (game->map[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
	calculate_perp_dist(game, ray);
}

void	render_3d(t_game *game)
{
	int		x;
	t_ray	ray;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		init_ray(game, &ray, x);
		perform_dda(game, &ray);
		draw_textured_wall(game, &ray, x);
		x++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img_3d, 0, 0);
}
