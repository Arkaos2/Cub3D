#include "../../includes/cub3d.h"

static int	is_empty_line(char *line)
{
	int	i;

	if (!line || line[0] == '\0')
		return (1);
	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

int	max_width(t_game *game)
{
	int	i;
	int	max;
	int	len;

	i = 0;
	max = 0;
	while (game->map[i])
	{
		len = ft_strlen(game->map[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

static int	store_line(t_game *game, char *line, int i)
{
	size_t	len;

	len = ft_strlen(line);
	while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r'))
	{
		line[len - 1] = '\0';
		len--;
	}
	if (is_empty_line(line))
		return (free(line), -1);
	game->map[i] = gc_strdup(game->gc, line);
	free(line);
	if (!game->map[i])
		return (-1);
	return (0);
}

int	fill_map(t_game *game, char *line)
{
	int	i;

	i = 0;
	game->map = gc_calloc(game->gc, sizeof(char *) * 1024);
	if (!game->map)
		return (-1);
	skip_space(game->map_fd, &line);
	while (line)
	{
		if (store_line(game, line, i) == -1)
			return (-1);
		i++;
		line = get_next_line(game->map_fd);
		if (i >= 1023)
			return (-1);
	}
	game->map[i] = NULL;
	game->height = i;
	if (i == 0)
		return (-1);
	return (0);
}



