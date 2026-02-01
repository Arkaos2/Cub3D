#include "cub3d.h"

static int	max_width(t_game *game)
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

int	fill_map(t_game *game, char *line)
{
	int		i;
	size_t	len;

	i = 0;
	game->map = gc_calloc(game->gc, sizeof(char *) * 1024);
	if (!game->map)
		return (-1);
	while (line)
	{
		len = ft_strlen(line);
		while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r'))
		{
			line[len - 1] = '\0';
			len--;
		}
		game->map[i] = gc_strdup(game->gc, line);
		free(line);
		if (!game->map[i])
			return (-1);
		i++;
		line = get_next_line(game->map_fd);
		if (i >= 1023)
			return (-1);
	}
	game->map[i] = NULL;
	game->height = i;
	return (0);
}

int	pad_map(t_game *game)
{
	int		i;
	int		len;
	char	*new_line;

	game->width = max_width(game);
	i = 0;
	while (game->map[i])
	{
		len = ft_strlen(game->map[i]);
		if (len < game->width)
		{
			new_line = gc_calloc(game->gc, game->width + 1);
			if (!new_line)
				return (-1);
			ft_memcpy(new_line, game->map[i], len);
			ft_memset(new_line + len, ' ', game->width - len);
			game->map[i] = new_line;
		}
		i++;
	}
	return (1);
}


