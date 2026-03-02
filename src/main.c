#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_game	*game;
	t_gc	*gc;
	char	*line;

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
		return (gc_destroy(gc), perror("open"), 1);
	line = fill_data(game);
	if (!line)
		return (gc_destroy(gc), printf("Error: map parsing failed\n"), 1);
	if (fill_map(game, line) < 0)
		return (gc_destroy(gc), printf("Error: map allocation failed\n"), 1);
	close(game->map_fd);
	pad_map(game);
	if (!map(game))
		return (gc_destroy(gc), printf("Error: invalid map\n"), 1);
	mlx_start(game);
	mlx_loop(game->mlx);
	gc_destroy(gc);
	return (0);
}

