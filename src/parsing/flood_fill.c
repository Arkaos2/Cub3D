#include "../../includes/cub3d.h"

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

static void	set_player_angle(t_game *game)
{
	if (game->dir == 'N')
		game->angle = -M_PI / 2;
	else if (game->dir == 'S')
		game->angle = M_PI / 2;
	else if (game->dir == 'E')
		game->angle = 0;
	else if (game->dir == 'W')
		game->angle = M_PI;
}

static int	check_line(t_game *game, int i, int *p)
{
	int	j;

	j = 0;
	while (game->map[i][j])
	{
		if (!is_valid_char(game->map[i][j]))
			return (0);
		if (is_player(game->map[i][j]))
		{
			(*p)++;
			game->player_x = j * 32;
			game->player_y = i * 32;
			game->dir = game->map[i][j];
			set_player_angle(game);
		}
		j++;
	}
	return (1);
}

int	check_element(t_game *game)
{
	int	i;
	int	p;

	i = 0;
	p = 0;
	while (game->map[i])
	{
		if (!check_line(game, i, &p))
			return (0);
		i++;
	}
	return (p == 1);
}
