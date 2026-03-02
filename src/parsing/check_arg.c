#include "../../includes/cub3d.h"

int	check_arg(char *args)
{
	int	len;

	len = ft_strlen(args);
	if (len < 4)
		return (0);
	if (ft_strcmp(args + (len - 4), ".cub") == 0)
		return (1);
	return (0);
}

static int	check_file(char *path)
{
	int	fd;

	if (!path)
		return (0);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

int	check_textures(t_game *game)
{
	if (!check_file(game->path_no))
		return (printf("Error: can't open texture: %s\n", game->path_no), 0);
	if (!check_file(game->path_so))
		return (printf("Error: can't open texture: %s\n", game->path_so), 0);
	if (!check_file(game->path_we))
		return (printf("Error: can't open texture: %s\n", game->path_we), 0);
	if (!check_file(game->path_ea))
		return (printf("Error: can't open texture: %s\n", game->path_ea), 0);
	return (1);
}

