#include "../../includes/cub3d.h"

void	cleanup(t_game *game)
{
	if (game->img_wall)
		mlx_destroy_image(game->mlx, game->img_wall);
	if (game->img_floor)
		mlx_destroy_image(game->mlx, game->img_floor);
	if (game->img_player)
		mlx_destroy_image(game->mlx, game->img_player);
	if (game->tex_no.img)
		mlx_destroy_image(game->mlx, game->tex_no.img);
	if (game->tex_so.img)
		mlx_destroy_image(game->mlx, game->tex_so.img);
	if (game->tex_we.img)
		mlx_destroy_image(game->mlx, game->tex_we.img);
	if (game->tex_ea.img)
		mlx_destroy_image(game->mlx, game->tex_ea.img);
	if (game->img_3d)
		mlx_destroy_image(game->mlx, game->img_3d);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
		mlx_destroy_display(game->mlx);
	free(game->mlx);
	gc_destroy(game->gc);
	exit(0);
}


static void	load_sprites(t_game *game)
{
	int	w;
	int	h;

	game->img_player = mlx_xpm_file_to_image(game->mlx, "texture/p.xpm", &w, &h);
	if (!game->img_player)
	{
		ft_printf("Error\n: Failed to load texture/p.xpm\n");
		cleanup(game);
	}
	game->img_wall = mlx_xpm_file_to_image(game->mlx, "texture/1.xpm", &w, &h);
	if (!game->img_wall)
	{
		ft_printf("Error\n: Failed to load texture/1.xpm\n");
		cleanup(game);
	}
	game->img_floor = mlx_xpm_file_to_image(game->mlx, "texture/0.xpm", &w, &h);
	if (!game->img_floor)
	{
		ft_printf("Error\n: Failed to load texture/0.xpm\n");
		cleanup(game);
	}
}

static void	load_texture(t_game *game, t_texture *tex, char *path)
{
	tex->width = TEX_SIZE;
	tex->height = TEX_SIZE;
	tex->img = mlx_xpm_file_to_image(game->mlx, path,
			&tex->width, &tex->height);
	if (!tex->img)
	{
		ft_printf("Error\n: Failed to load %s\n", path);
		cleanup(game);
	}
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp,
			&tex->line_len, &tex->endian);
}

void	load_textures(t_game *game)
{
	load_texture(game, &game->tex_no, game->path_no);
	load_texture(game, &game->tex_so, game->path_so);
	load_texture(game, &game->tex_we, game->path_we);
	load_texture(game, &game->tex_ea, game->path_ea);
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

void	draw_map(t_game *game)
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
	game->win = mlx_new_window(game->mlx, 1280, 720, "cub3D");
	if (!game->win)
	{
		ft_printf("Error\n: impossible de créer la fenêtre\n");
		gc_destroy(game->gc);
		exit(1);
	}
	load_sprites(game);
	load_textures(game);
	game->img_3d = mlx_new_image(game->mlx, 1280, 720);
	if (!game->img_3d)
	{
		ft_printf("Error\n: impossible de créer l'image 3D\n");
		cleanup(game);
	}
	game->addr_3d = mlx_get_data_addr(game->img_3d, &game->bpp_3d,
			&game->line_len_3d, &game->endian_3d);
	setup_hooks(game);
	render_3d(game);
	return 1;
}
