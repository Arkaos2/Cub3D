/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 16:52:42 by saibelab          #+#    #+#             */
/*   Updated: 2026/03/04 16:59:26 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	try_no_so(t_game *game, char *line, int *i)
{
	skip_whitespace(line, i);
	if (line[*i] == 'N' && line[*i + 1] == 'O')
	{
		if (game->has_no)
			return (0);
		game->has_no = 1;
		*i += 2;
		skip_whitespace(line, i);
		game->path_no = gc_strtrim(game->gc, line + *i, " \t\n\r");
		return (1);
	}
	if (line[*i] == 'S' && line[*i + 1] == 'O')
	{
		if (game->has_so)
			return (0);
		game->has_so = 1;
		*i += 2;
		skip_whitespace(line, i);
		game->path_so = gc_strtrim(game->gc, line + *i, " \t\n\r");
		return (1);
	}
	return (-1);
}

static int	try_we_ea(t_game *game, char *line, int *i)
{
	if (line[*i] == 'W' && line[*i + 1] == 'E')
	{
		if (game->has_we)
			return (0);
		game->has_we = 1;
		*i += 2;
		skip_whitespace(line, i);
		game->path_we = gc_strtrim(game->gc, line + *i, " \t\n\r");
		return (1);
	}
	if (line[*i] == 'E' && line[*i + 1] == 'A')
	{
		if (game->has_ea)
			return (0);
		game->has_ea = 1;
		*i += 2;
		skip_whitespace(line, i);
		game->path_ea = gc_strtrim(game->gc, line + *i, " \t\n\r");
		return (1);
	}
	return (-1);
}

int	grab_path(t_game *game, char *line, int *i)
{
	int	ret;

	ret = try_no_so(game, line, i);
	if (ret != -1)
		return (ret);
	ret = try_we_ea(game, line, i);
	if (ret != -1)
		return (ret);
	return (0);
}

int	grab_color(t_game *game, char *line, int *i)
{
	skip_whitespace(line, i);
	if (line[*i] == 'F')
	{
		if (game->has_f)
			return (0);
		1 && (game->has_f = 1, *i += 1);
		skip_whitespace(line, i);
		game->f_color = parse_color(line + *i);
		if (game->f_color == -1)
			return (0);
		return (1);
	}
	if (line[*i] == 'C')
	{
		if (game->has_c)
			return (0);
		game->has_c = 1;
		*i += 1;
		skip_whitespace(line, i);
		game->c_color = parse_color(line + *i);
		if (game->c_color == -1)
			return (0);
		return (1);
	}
	return (0);
}
