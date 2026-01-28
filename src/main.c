#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_game	*game;
	t_gc	*gc;

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
	if (fill_map(game))
		return (printf("Error: map parsing failed\n"), 1);
	if(!check_void(game))
		return(printf("lose"),0);
	printf("win");

	return (0);
}



