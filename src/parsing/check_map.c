#include "../../includes/cub3d.h"

static int	grab_path(t_game *game, char *line, int *i)
{
	skip_whitespace(line, i);
	if (line[*i] == 'N' && line[*i + 1] == 'O')
	{
		if (game->has_no)
			return (0);
		game->has_no = 1;
		*i += 2;
		skip_whitespace(line, i);
		game->path_no = gc_strdup(game->gc, line + *i);
		return (1);
	}
	if (line[*i] == 'S' && line[*i + 1] == 'O')
	{
		if (game->has_so)
			return (0);
		game->has_so = 1;
		*i += 2;
		skip_whitespace(line, i);
		game->path_so = gc_strdup(game->gc, line + *i);
		return (1);
	}
	if (line[*i] == 'W' && line[*i + 1] == 'E')
	{
		if (game->has_we)
			return (0);
		game->has_we = 1;
		*i += 2;
		skip_whitespace(line, i);
		game->path_we = gc_strdup(game->gc, line + *i);
		return (1);
	}
	if (line[*i] == 'E' && line[*i + 1] == 'A')
	{
		if (game->has_ea)
			return (0);
		game->has_ea = 1;
		*i += 2;
		skip_whitespace(line, i);
		game->path_ea = gc_strdup(game->gc, line + *i);
		return (1);
	}
	return (0);
}

static int	read_color_value(char *s, int *i)
{
	int	val;
	int	start;

	skip_whitespace(s, i);
	start = *i;
	if (!ft_isdigit(s[*i]))
		return (-1);
	val = ft_atoi(s + *i);
	while (ft_isdigit(s[*i]))
		(*i)++;
	if (*i == start || val < 0 || val > 255)
		return (-1);
	return (val);
}

int	parse_color(char *s)
{
	int	i;
	int	r;
	int	g;
	int	b;

	i = 0;
	r = read_color_value(s, &i);
	if (r < 0 || s[i++] != ',')
		return (-1);
	g = read_color_value(s, &i);
	if (g < 0 || s[i++] != ',')
		return (-1);
	b = read_color_value(s, &i);
	if (b < 0)
		return (-1);
	skip_whitespace(s, &i);
	if (s[i])
		return (-1);
	return ((r << 16) | (g << 8) | b);
}

static int	grab_color(t_game *game, char *line, int *i)
{
	skip_whitespace(line, i);
	if (line[*i] == 'F')
	{
		if (game->has_f)
			return (0);
		game->has_f = 1;
		*i += 1;
		skip_whitespace(line, i);
		game->f_color = parse_color(line + *i);
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
		return (1);
	}
	return (0);
}

static int	process_data_line(t_game *game, char *line)
{
	int i;

	i = 0;
	skip_whitespace(line, &i);
	if (is_texture_id(line, i))
	{
		if (!grab_path(game, line, &i))
			return (0);
		return (1);
	}
	else if (is_color_id(line, i))
	{
		if (!grab_color(game, line, &i))
			return (0);
		return (1);
	}
	return (-1);
}

char *fill_data(t_game *game)
{
	char *line;
	int count;
	int result;

	count = 0;
	line = get_next_line(game->map_fd);
	while (line && count < 6)
	{
		if (!is_whitespace(line))
		{
			result = process_data_line(game, line);
			if (result == 1)
				count++;
			else if (result == 0 || result == -1)
				return (free(line), NULL);
		}
		free(line);
		line = get_next_line(game->map_fd);
	}
	if (!game->has_no || !game->has_so || !game->has_we || !game->has_ea
		|| !game->has_f || !game->has_c)
		return (free(line), NULL);
	return (line);
}
