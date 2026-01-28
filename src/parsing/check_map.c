#include "../../includes/cub3d.h"

static int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == '\n' || line[i] == '\0')
		return (1);
	return (0);
}

int	fill_map(t_game *game)
{
	char	*line;
	int		i;
	int		in_map;
	int		j;

	i = 0;
	in_map = 0;
	game->map = gc_calloc(game->gc, sizeof(char *) * 100);
	if (!game->map)
		return (1);
	while ((line = get_next_line(game->map_fd)))
	{
		if (!in_map)
		{
			j = 0;
			while (line[j] && line[j] == ' ')
				j++;
			if (line[j] == '1')
				in_map = 1;
			else
			{
				free(line);
				continue;
			}
		}
		if (is_empty_line(line))
			return (free(line), printf("Error: empty line in map\n"), 1);
		game->map[i++] = gc_strdup(game->gc, line);
		free(line);
	}
	if(i > 100)
		return (1);
	game->map[i] = NULL;
	return (0);
}

