/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 16:53:50 by saibelab          #+#    #+#             */
/*   Updated: 2026/03/04 16:53:50 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	load_sprites(t_game *game)
{
	int	w;
	int	h;

	game->img_player = mlx_xpm_file_to_image(game->mlx,
			"texture/p.xpm", &w, &h);
	if (!game->img_player)
	{
		ft_printf("Error\n: Failed to load texture/p.xpm\n");
		cleanup(game);
	}
	game->img_wall = mlx_xpm_file_to_image(game->mlx,
			"texture/1.xpm", &w, &h);
	if (!game->img_wall)
	{
		ft_printf("Error\n: Failed to load texture/1.xpm\n");
		cleanup(game);
	}
	game->img_floor = mlx_xpm_file_to_image(game->mlx,
			"texture/0.xpm", &w, &h);
	if (!game->img_floor)
	{
		ft_printf("Error\n: Failed to load texture/0.xpm\n");
		cleanup(game);
	}
}

static void	load_texture(t_game *game, t_texture *tex, char *path)
{
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

int	mlx_start(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (gc_destroy(game->gc), exit(1), 0);
	game->win = mlx_new_window(game->mlx, 1280, 720, "cub3D");
	if (!game->win)
	{
		ft_printf("Error\n: impossible de creer la fenetre\n");
		return (gc_destroy(game->gc), exit(1), 0);
	}
	load_sprites(game);
	load_textures(game);
	game->img_3d = mlx_new_image(game->mlx, 1280, 720);
	if (!game->img_3d)
	{
		ft_printf("Error\n: impossible de creer l'image 3D\n");
		cleanup(game);
	}
	game->addr_3d = mlx_get_data_addr(game->img_3d, &game->bpp_3d,
			&game->line_len_3d, &game->endian_3d);
	setup_hooks(game);
	render_3d(game);
	return (1);
}
