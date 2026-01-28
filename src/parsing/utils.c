#include "cub3d.h"

int	count_lines(t_game *game)
{

}

char	**map_parse(t_game *game, int nb_lines)
{
	int		i;
	char	**map_copy;

	i = 0;
	map_copy = gc_malloc(game->gc, sizeof(char *) * (nb_lines + 1));
	if (!map_copy)
		return (NULL);
	while (i < nb_lines)
	{
		map_copy[i] = gc_strdup(game->gc, game->map[i]);
		if (!map_copy[i])
			return (NULL);
		i++;
	}
	map_copy[i] = NULL;
	return (map_copy);
}
