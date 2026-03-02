#include "../../includes/cub3d.h"

static int	check_c(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (ft_is_whitespace(s[i]))
			i++;
		else
			return (1);
	}
	return (0);
}

void	skip_space(int fd, char **temp)
{
	if (!temp || !*temp)
		return ;
	while (*temp)
	{
		if (check_c(*temp))
			return ;
		free(*temp);
		*temp = get_next_line(fd);
	}
}
