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
	char	*tmp;

	i = 0;
	game->map = gc_calloc(game->gc, sizeof(char *) * 1024);
	if (!game->map)
		return (-1);
	while (line)
	{
		tmp = ft_strtrim(line, "\n");
		free(line);
		if (!tmp)
			return (-1);
		game->map[i] = gc_strdup(game->gc, tmp);
		free(tmp);
		if (!game->map[i])
			return (-1);
		i++;
		if (i >= 1024)
			break;
		line = get_next_line(game->map_fd);
	}
	game->map[i] = NULL;
	game->height = i;
	return (0);
}

int pad_map(t_game *game)
{
	int i;
	int len;
	char *new_line;
	int j;

	game->width = max_width(game);
	i = 0;
	while (game->map[i])
	{
		len = ft_strlen(game->map[i]);
		if (len < game->width)
		{
			new_line = gc_calloc(game->gc, game->width + 1);
			if (!new_line)
				return -1;
			j = 0;
			while (j < len)
			{
				new_line[j] = game->map[i][j];
				j++;
			}
			while (j < game->width)
				new_line[j++] = ' ';
			new_line[j] = '\0';
			game->map[i] = new_line;
		}
		i++;
	}
	return 1;
}

