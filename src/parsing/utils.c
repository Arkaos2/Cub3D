#include "cub3d.h"

int	count_lines(t_game *game)
{
	int	i;

	i = 0;
	while(game->map[i])
		i++;
	return (i);
}

char	**map_parse(t_game *game)
{
	int		i;
	char	**map_copy;

	i = 0;
	map_copy = gc_calloc(game->gc, sizeof(char *) * (count_lines(game) + 1));
	if (!map_copy)
		return (NULL);
	while (game->map[i])
	{
		map_copy[i] = gc_strdup(game->gc, game->map[i]);
		if (!map_copy[i])
			return (NULL);
		i++;
	}
	map_copy[i] = NULL;
	return (map_copy);
}

int	is_color_id(char *line, int i)
{
	if (line[i] == 'F' && ft_is_whitespace(line[i + 1]))
		return (1);
	if (line[i] == 'C' && ft_is_whitespace(line[i + 1]))
		return (1);
	return (0);
}

int	is_texture_id(char *line, int i)
{
	if (line[i] == 'N' && line[i + 1] == 'O')
		return (1);
	if (line[i] == 'S' && line[i + 1] == 'O')
		return (1);
	if (line[i] == 'W' && line[i + 1] == 'E')
		return (1);
	if (line[i] == 'E' && line[i + 1] == 'A')
		return (1);
	return (0);
}
static int	check_c(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (ft_is_whitespace(s[i]))
			i++;
		else
			return (1);
	}
	return (0);
}

void	skip_space(int fd, char **temp)
{
	if (!temp || !*temp)
		return ;
	while (*temp)
	{
		if (check_c(*temp))
			return ;
		free(*temp);
		*temp = get_next_line(fd);
	}
}
