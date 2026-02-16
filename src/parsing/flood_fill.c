#include "cub3d.h"

static int	is_valid_char(char c)
{
	return (ft_is_whitespace(c) || c == '1' || c == '0'
		|| c == 'N' || c == 'E'
		|| c == 'W' || c == 'S');
}

static int	is_player(char c)
{
	return (c == 'N' || c == 'E' || c == 'W' || c == 'S');
}

int	check_element(t_game *game)
{
	int	i;
	int	j;
	int	player;

	i = 0;
	player = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (!is_valid_char(game->map[i][j]))
				return (0);
			if (is_player(game->map[i][j]))
			{
				player++;
				game->player_x = j;
				game->player_y = i;
				game->dir = game->map[i][j];
			}
			j++;
		}
		i++;
	}
	return (player == 1);
}

int flood_fill(t_game *g, int y, int x)
{
	if (y < 0 || y >= g->height + 2 || x < 0 || x >= g->width)
		return (0);
	if (g->map_copy[y][x] == 'U' || g->map_copy[y][x] == '.')
		return (0);
	if (g->map_copy[y][x] == '1' || g->map_copy[y][x] == 'V')
		return (1);
	if (g->map_copy[y][x] == ' ' || g->map_copy[y][x] == '\t')
		return (0);
	g->map_copy[y][x] = 'V';
	if (!flood_fill(g, y + 1, x))
		return (0);
	if (!flood_fill(g, y - 1, x))
		return (0);
	if (!flood_fill(g, y, x + 1))
		return (0);
	if (!flood_fill(g, y, x - 1))
		return (0);
	return (1);
}


int	map(t_game *game)
{
	int	i;
	int	j;

	if(!check_element(game))
	{
		printf("check map fail\n");
		return 0;
	}
	printf("player y=%d x=%d\n", game->player_y, game->player_x);
	if (!flood_fill(game, game->player_y + 1, game->player_x))
	{
		printf("map ouverte\n");
		return (0);
	}
	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == '0' && game->map_copy[i + 1][j] != 'V')
			{
				if (!flood_fill(game, i + 1, j))
				{
					printf("0 isole non ferme trouve\n");
					return (0);
				}
			}
			j++;
		}
		i++;
	}
	return 1;
}
