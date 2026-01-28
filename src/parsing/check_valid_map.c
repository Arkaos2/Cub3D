#include "cub3d.h"

static int	is_floor(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	is_void(char **map, int i, int j)
{
	if (i < 0 || j < 0)
		return (1);
	if (!map[i])
		return (1);
	if (j >= (int)ft_strlen(map[i]))
		return (1);
	if (map[i][j] == ' ' || map[i][j] == '\0')
		return (1);
	return (0);
}

static int	check_cell(char **map, int i, int j)
{
	if (is_void(map, i, j - 1))
		return (0);
	if (is_void(map, i, j + 1))
		return (0);
	if (is_void(map, i - 1, j))
		return (0);
	if (is_void(map, i + 1, j))
		return (0);
	return (1);
}

int	check_void(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (is_floor(game->map[i][j]))
			{
				if (!check_cell(game->map, i, j))
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	flood_fill(char **map, int x, int y)
{
	if(!map && !map[x][y] && x < 0 && y < 0 && map[x] != '\0' && map[x][y] != '\0')
		return (-1);


}
