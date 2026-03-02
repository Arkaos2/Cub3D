#include "../../includes/cub3d.h"

static void	draw_ceiling(t_game *game, int x, int draw_start)
{
	int	y;

	y = 0;
	while (y < draw_start)
	{
		put_pixel(game, x, y, game->c_color);
		y++;
	}
}

static void	draw_floor(t_game *game, int x, int draw_end)
{
	int	y;

	y = draw_end;
	while (y < SCREEN_HEIGHT)
	{
		put_pixel(game, x, y, game->f_color);
		y++;
	}
}

static void	draw_wall_slice(t_game *game, t_draw *d, int x)
{
	int		y;
	int		tex_y;
	int		color;

	y = d->draw_start;
	while (y < d->draw_end)
	{
		tex_y = (int)d->tex_pos & (TEX_SIZE - 1);
		d->tex_pos += d->step;
		color = get_texture_color(d->tex->addr, d->tex->line_len,
				d->tex->bpp, d->ray->tex_x, tex_y);
		put_pixel(game, x, y, color);
		y++;
	}
}

static void	init_draw_params(t_game *game, t_ray *ray, t_draw *d)
{
	d->ray = ray;
	d->line_height = calculate_line_height(ray->perp_wall_dist);
	d->draw_start = -d->line_height / 2 + SCREEN_HEIGHT / 2;
	if (d->draw_start < 0)
		d->draw_start = 0;
	d->draw_end = d->line_height / 2 + SCREEN_HEIGHT / 2;
	if (d->draw_end >= SCREEN_HEIGHT)
		d->draw_end = SCREEN_HEIGHT - 1;
	calculate_texture_x(game, ray);
	select_texture(game, ray, &d->tex);
	d->step = 1.0 * TEX_SIZE / d->line_height;
	d->tex_pos = (d->draw_start - SCREEN_HEIGHT / 2
			+ d->line_height / 2) * d->step;
}

void	draw_textured_wall(t_game *game, t_ray *ray, int x)
{
	t_draw	d;

	init_draw_params(game, ray, &d);
	draw_ceiling(game, x, d.draw_start);
	draw_wall_slice(game, &d, x);
	draw_floor(game, x, d.draw_end);
}
