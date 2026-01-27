#include "../../includes/cub3d.h"

int	check_arg(char *args)
{
	int	len;

	len = ft_strlen(args);
	if (len < 4)
		return (0);
	if(ft_strcmp(args + (len - 4), ".cub") == 0)
		return (1);
	return (0);
}

