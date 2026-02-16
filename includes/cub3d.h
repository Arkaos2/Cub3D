/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 15:39:24 by saibelab          #+#    #+#             */
/*   Updated: 2026/02/11 14:21:20 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libs/libft/libft.h"

# include <stdio.h>
# include <math.h>
# include <errno.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/time.h>

typedef struct s_game
{
	t_gc	*gc;

	char	**map;
	char	**map_copy;


	char	*path_no;
	char	*path_so;
	char	*path_we;
	char	*path_ea;
	int		has_no;
	int		has_so;
	int		has_we;
	int		has_ea;
	int		has_f;
	int		has_c;

	int		f_color;
	int		c_color;

	int		player_y;
	int		player_x;
	char	dir;

	int		height;
	int		width;

	int		map_fd;
}			t_game;

typedef struct s_gcnode
{
	void			*ptr;
	struct s_gcnode	*next;
}				t_gcnode;

typedef struct s_gc
{
	t_gcnode		*head;
}	t_gc;

t_gcnode	*new_node(void *ptr);
t_gc		*gc_new(void);
void		*gc_calloc(t_gc *gc, size_t size);
void		gc_destroy(t_gc *gc);
char		*gc_strdup(t_gc *gc, const char *s);
char		*gc_strndup(t_gc *gc, const char *s, int n);
char		*gc_strjoin(t_gc *gc, const char *s1, const char *s2);
char		*gc_substr(t_gc *gc, char const *s, unsigned int start, size_t len);

int			is_texture_id(char *line, int i);
int			is_color_id(char *line, int i);

int			fill_map(t_game *game, char *line);
int			pad_map(t_game *game);

int			check_void(t_game *game);
int			check_arg(char *args);
char		*fill_data(t_game *game);

int		flood_fill(t_game *g, int y, int x);
int		map(t_game *game);

void	skip_space(int fd, char **temp);


#endif
