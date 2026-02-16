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
	skip_space(game->map_fd, &line);
	while (line)
	{
		len = ft_strlen(line);
		while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r'))
			1 && (line[len - 1] = '\0', len--);
		game->map[i] = gc_strdup(game->gc, line);
		if(!game->map[i])
			return (-1);
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

static char	*fill(t_game *game)
{
	char	*res;
	int		i;
	int s = 0;


	res = gc_calloc(game->gc, sizeof(char) * (game->width + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (i < game->width)
	{
		res[i] = '.';
		s++;
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
	while (y < game->width )
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



