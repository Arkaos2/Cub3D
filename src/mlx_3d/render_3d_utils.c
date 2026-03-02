#include "../../includes/cub3d.h"

void	put_pixel(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
	{
		dst = game->addr_3d + (y * game->line_len_3d + x
				* (game->bpp_3d / 8));
		*(unsigned int *)dst = color;
	}
}

int	get_texture_color(char *addr, int line_len, int bpp, int x, int y)
{
	char	*pixel;

	pixel = addr + (y * line_len + x * (bpp / 8));
	return (*(unsigned int *)pixel);
}

void	select_texture(t_game *game, t_ray *ray, t_texture **tex)
{
	if (ray->side == 0 && ray->step_x > 0)
		*tex = &game->tex_ea;
	else if (ray->side == 0 && ray->step_x < 0)
		*tex = &game->tex_we;
	else if (ray->side == 1 && ray->step_y > 0)
		*tex = &game->tex_so;
	else
		*tex = &game->tex_no;
}

void	calculate_texture_x(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
		ray->wall_x = (game->player_y + 16) / 32.0
			+ ray->perp_wall_dist * ray->raydir_y;
	else
		ray->wall_x = (game->player_x + 16) / 32.0
			+ ray->perp_wall_dist * ray->raydir_x;
	ray->wall_x -= floor((ray->wall_x));
	ray->tex_x = (int)(ray->wall_x * (double)TEX_SIZE);
	if (ray->side == 0 && ray->raydir_x > 0)
		ray->tex_x = TEX_SIZE - ray->tex_x - 1;
	if (ray->side == 1 && ray->raydir_y < 0)
		ray->tex_x = TEX_SIZE - ray->tex_x - 1;
}

int	calculate_line_height(double perp_wall_dist)
{
	double	dist;

	dist = perp_wall_dist;
	if (dist < 0.1)
		dist = 0.1;
	return ((int)(SCREEN_HEIGHT / dist));
}
