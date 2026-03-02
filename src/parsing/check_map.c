#include "../../includes/cub3d.h"

static int	read_color_value(char *s, int *i)
{
	int	start;
	int	val;

	skip_whitespace(s, i);
	start = *i;
	if (!ft_isdigit(s[*i]))
		return (-1);
	while (ft_isdigit(s[*i]))
		(*i)++;
	val = ft_atoi(s + start);
	if (val < 0 || val > 255)
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
	if (r < 0 || s[i] != ',')
		return (-1);
	i++;
	g = read_color_value(s, &i);
	if (g < 0 || s[i] != ',')
		return (-1);
	i++;
	b = read_color_value(s, &i);
	if (b < 0)
		return (-1);
	skip_whitespace(s, &i);
	if (s[i] != '\0')
		return (-1);
	return ((r << 16) | (g << 8) | b);
}

static int	process_data_line(t_game *game, char *line)
{
	int	i;

	i = 0;
	skip_whitespace(line, &i);
	if (is_texture_id(line, i))
		return (grab_path(game, line, &i));
	if (is_color_id(line, i))
		return (grab_color(game, line, &i));
	return (-1);
}

char	*fill_data(t_game *game)
{
	char	*line;
	int		count;
	int		result;

	count = 0;
	line = get_next_line(game->map_fd);
	while (line && count < 6)
	{
		if (!is_whitespace(line))
		{
			result = process_data_line(game, line);
			if (result == 1)
				count++;
			else
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
