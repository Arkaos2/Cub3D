/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 16:52:53 by saibelab          #+#    #+#             */
/*   Updated: 2026/03/04 16:52:54 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	flood_fill(t_game *g, int y, int x)
{
	if (y < 0 || y >= g->height + 2 || x < 0 || x >= g->width)
		return (0);
	if (g->map_copy[y][x] == 'U' || g->map_copy[y][x] == '.')
		return (0);
	if (g->map_copy[y][x] == '1' || g->map_copy[y][x] == 'V')
		return (1);
	if (g->map_copy[y][x] == ' ' || g->map_copy[y][x] == '\t')
		return (0);
	g->map_copy[y][x] = 'V';
	if (!flood_fill(g, y + 1, x))
		return (0);
	if (!flood_fill(g, y - 1, x))
		return (0);
	if (!flood_fill(g, y, x + 1))
		return (0);
	if (!flood_fill(g, y, x - 1))
		return (0);
	return (1);
}

static int	check_isolated(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == '0'
				&& game->map_copy[i + 1][j] != 'V')
			{
				if (!flood_fill(game, i + 1, j))
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	map(t_game *game)
{
	if (!check_element(game))
		return (0);
	game->x = game->player_x / 32;
	game->y = game->player_y / 32;
	if (!flood_fill(game, game->player_y / 32 + 1, game->player_x / 32))
		return (0);
	return (check_isolated(game));
}
