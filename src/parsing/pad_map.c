/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pad_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 16:52:59 by saibelab          #+#    #+#             */
/*   Updated: 2026/03/04 16:53:00 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static char	*fill(t_game *game)
{
	char	*res;
	int		i;

	res = gc_calloc(game->gc, sizeof(char) * (game->width + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (i < game->width)
	{
		res[i] = '.';
		i++;
	}
	res[i] = '\0';
	return (res);
}

static int	copy_pad_line(t_game *game, int i, int j)
{
	int	len;
	int	y;

	len = ft_strlen(game->map[j]);
	game->map_copy[i] = gc_calloc(game->gc, sizeof(char) * (game->width + 1));
	if (!game->map_copy[i])
		return (-1);
	ft_strlcpy(game->map_copy[i], game->map[j], len + 1);
	y = len;
	while (y < game->width)
	{
		game->map_copy[i][y] = '.';
		y++;
	}
	game->map_copy[i][y] = '\0';
	return (0);
}

int	pad_map(t_game *game)
{
	int	i;
	int	j;

	game->map_copy = gc_calloc(game->gc, sizeof(char *) * (game->height + 3));
	if (!game->map_copy)
		return (-1);
	game->width = max_width(game);
	i = 0;
	game->map_copy[i] = fill(game);
	if (!game->map_copy[i])
		return (-1);
	i++;
	j = 0;
	while (game->map[j])
	{
		if (copy_pad_line(game, i, j) == -1)
			return (-1);
		i++;
		j++;
	}
	game->map_copy[i] = fill(game);
	if (!game->map_copy[i])
		return (-1);
	i++;
	return (game->map_copy[i] = NULL, 1);
}
