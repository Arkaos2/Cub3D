#include "../../includes/cub3d.h"

void	init_ray_position(t_game *game, t_ray *ray, int x)
{
	double	pos_x;
	double	pos_y;

	pos_x = (game->player_x + 16) / 32.0;
	pos_y = (game->player_y + 16) / 32.0;
	ray->camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
	ray->map_x = (int)pos_x;
	ray->map_y = (int)pos_y;
}

void	init_ray_direction(t_game *game, t_ray *ray)
{
	ray->raydir_x = cos(game->angle) + sin(game->angle) * ray->camera_x;
	ray->raydir_y = sin(game->angle) - cos(game->angle) * ray->camera_x;
}

void	init_ray_delta(t_ray *ray)
{
	ray->deltadist_x = fabs(1 / ray->raydir_x);
	ray->deltadist_y = fabs(1 / ray->raydir_y);
	ray->hit = 0;
}

void	init_ray_step(t_game *game, t_ray *ray)
{
	double	pos_x;
	double	pos_y;

	pos_x = (game->player_x + 16) / 32.0;
	pos_y = (game->player_y + 16) / 32.0;
	if (ray->raydir_x < 0)
	{
		ray->step_x = -1;
		ray->sidedist_x = (pos_x - ray->map_x) * ray->deltadist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->sidedist_x = (ray->map_x + 1.0 - pos_x) * ray->deltadist_x;
	}
	if (ray->raydir_y < 0)
	{
		ray->step_y = -1;
		ray->sidedist_y = (pos_y - ray->map_y) * ray->deltadist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->sidedist_y = (ray->map_y + 1.0 - pos_y) * ray->deltadist_y;
	}
}

void	init_ray(t_game *game, t_ray *ray, int x)
{
	init_ray_position(game, ray, x);
	init_ray_direction(game, ray);
	init_ray_delta(ray);
	init_ray_step(game, ray);
}
