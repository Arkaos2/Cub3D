#include "../includes/cub3d.h"

int	fill_map(t_game *game)
{
	int	line;
	int	i;

	i = 0;
	game->map = gc_calloc(game->gc, sizeof(char **));
	line = get_next_line(game->map_fd);
	while(line && line[0] == '1' || line[0] == ' ')
	{
		game->map[i] = gc_calloc(game->gc, sizeof(char *))
	}
}

int	main(int argc, char **argv)
{
	t_game	*game;

	if (argc != 2)
		return (printf("Error\n: wrong number of arguments\n"), 1);
	game->gc = gc_new();
	game->map_fd = open(argv[1], O_RDONLY);
	return (0);
}

