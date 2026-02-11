#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_game	*game;
	t_gc	*gc;
	char	*line;
	int		i;

	if (argc != 2)
		return (printf("Error: wrong number of arguments\n"), 1);
	gc = gc_new();
	if (!gc)
		return (1);
	game = gc_calloc(gc, sizeof(t_game));
	if (!game)
		return (1);
	game->gc = gc;
	game->map_fd = open(argv[1], O_RDONLY);
	if (game->map_fd < 0)
		return (perror("open"), 1);
	line = fill_data(game);
	if (!line)
		return (printf("Error: map parsing failed\n"), 1);
	if (fill_map(game, line) < 0)
		return (printf("Error: map allocation failed\n"), 1);
	close(game->map_fd);
	pad_map(game);
	i = 0;
	while (game->map_copy[i])
	{
		printf("[%s]\n", game->map_copy[i]);
		i++;
	}

	return (0);
}

