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
# include "../libs/minilibx-linux/mlx.h"

# include <stdio.h>
# include <math.h>
# include <errno.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/time.h>

# define SCREEN_WIDTH 1280
# define SCREEN_HEIGHT 720
# define TEX_SIZE 64

typedef struct s_gcnode
{
	void			*ptr;
	struct s_gcnode	*next;
}				t_gcnode;

typedef struct s_gc
{
	t_gcnode		*head;
}	t_gc;

typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_texture;

typedef struct s_ray
{
	double	camera_x;
	double	raydir_x;
	double	raydir_y;
	int		map_x;
	int		map_y;
	double	sidedist_x;
	double	sidedist_y;
	double	deltadist_x;
	double	deltadist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	double	wall_x;
	int		tex_x;
}	t_ray;

typedef struct s_draw
{
	t_ray		*ray;
	t_texture	*tex;
	int			line_height;
	int			draw_start;
	int			draw_end;
	double		step;
	double		tex_pos;
}	t_draw;

typedef struct s_game
{
	t_gc		*gc;

	char		**map;
	char		**map_copy;

	void		*mlx;
	void		*win;

	// Sprites pour la minimap
	void		*img_player;
	void		*img_floor;
	void		*img_wall;

	// Textures pour le rendu 3D
	t_texture	tex_no;
	t_texture	tex_so;
	t_texture	tex_we;
	t_texture	tex_ea;

	// Buffer pour le rendu 3D
	void		*img_3d;
	char		*addr_3d;
	int			bpp_3d;
	int			line_len_3d;
	int			endian_3d;

	int			x;
	int			y;

	// Chemins des textures
	char		*path_no;
	char		*path_so;
	char		*path_we;
	char		*path_ea;
	int			has_no;
	int			has_so;
	int			has_we;
	int			has_ea;
	int			has_f;
	int			has_c;

	// Couleurs sol et plafond
	int			f_color;
	int			c_color;

	// Position et orientation du joueur
	int			player_y;
	int			player_x;
	char		dir;
	double		angle;

	// Dimensions de la map
	int			height;
	int			width;

	int			map_fd;
}			t_game;

t_gcnode	*new_node(void *ptr);
t_gc		*gc_new(void);
void		*gc_calloc(t_gc *gc, size_t size);
void		gc_destroy(t_gc *gc);
char		*gc_strdup(t_gc *gc, const char *s);
char		*gc_strndup(t_gc *gc, const char *s, int n);
char		*gc_strjoin(t_gc *gc, const char *s1, const char *s2);
char		*gc_substr(t_gc *gc, char const *s, unsigned int start, size_t len);
char		*gc_strtrim(t_gc *gc, char const *s1, char const *set);

int			check_arg(char *args);
int			parse_color(char *s);
char		*fill_data(t_game *game);
int			fill_map(t_game *game, char *line);
int			pad_map(t_game *game);
int			check_element(t_game *game);
int			flood_fill(t_game *g, int y, int x);
int			map(t_game *game);
int			count_lines(t_game *game);
int			is_color_id(char *line, int i);
int			is_texture_id(char *line, int i);
void		skip_space(int fd, char **temp);

int			mlx_start(t_game *game);
void		cleanup(t_game *game);
void		draw_map(t_game *game);
void		draw_player_direction(t_game *game);
void		draw_rays(t_game *game);
void		render_3d(t_game *game);
void		setup_hooks(t_game *game);
int			can_move(t_game *game, int n_px, int n_py);
int			move_player(int keycode, t_game *game);
int			is_wall(t_game *game, int x, int y);
void		load_textures(t_game *game);

void		init_ray(t_game *game, t_ray *ray, int x);
void		perform_dda(t_game *game, t_ray *ray);
void		draw_textured_wall(t_game *game, t_ray *ray, int x);
void		put_pixel(t_game *game, int x, int y, int color);
int			get_texture_color(char *addr, int line_len, int bpp, int x, int y);
void		select_texture(t_game *game, t_ray *ray, t_texture **tex);
void		calculate_texture_x(t_game *game, t_ray *ray);
int			calculate_line_height(double perp_wall_dist);


#endif
