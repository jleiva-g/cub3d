/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregueir <gregueir@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 18:46:53 by jleiva-g          #+#    #+#             */
/*   Updated: 2026/05/28 16:31:42 by gregueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/inc/libft.h"
# include "MLX42/include/MLX42/MLX42.h"
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <sys/time.h>
# include <math.h>
# include <limits.h>
# include <float.h>

# define WIDTH 1920
# define HEIGHT 1080
# define FOV 0.66f
# define ROTATE_SPEED 0.04f
# define MOVE_SPEED 0.06f
# define MM_TILE 16
# define MM_SIZE 21

typedef enum e_flags
{
	NO,
	SO,
	EA,
	WE,
	F,
	C
}	t_flags;

typedef struct s_point
{
	float	x;
	float	y;
}	t_point;

typedef struct s_tex
{
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*west;
	mlx_texture_t	*east;
	mlx_texture_t	*door;
	mlx_texture_t	**weapon;
}	t_tex;

typedef struct s_player
{
	t_point	pos;
	t_point	dir;
	t_point	plane;
}	t_player;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		floor_color;
	int		ceil_color;
}	t_map;

typedef struct s_game
{
	mlx_t		*mlx;
	mlx_image_t	*view;
	mlx_image_t	*mmap;
	mlx_image_t	*weapon;
	t_map		map;
	t_player	player;
	float		mouse_x;
	float		mouse_delta;
	t_tex		tex;
	int			key[6];
	char		*wname;
}	t_game;

typedef struct s_ray
{
	t_point	ray_dir;
	t_point	cell;
	t_point	cell_dist;
	t_point	grid_dist;
	t_point	step;
	int		side;
	int		is_door;
	float	wall_dist;
	int		wall_height;
	int		wall_start;
	int		wall_end;
	float	wall_x;
}	t_ray;

// cleanup
void			cleanup(t_game game);

// utils
int				is_not_wall(char cell);

// init
int				init(t_game *game, char **argv);
int				validate(t_game *game, char **argv);
int				validate_line(t_game *game, char *line);

// textures
mlx_texture_t	*get_texture(t_game *game, t_ray ray);
uint32_t		get_pixel(mlx_texture_t *tex, int x, int y);

// raycasting
void			set_up_ray(t_player p, t_ray *r, int x);
void			set_up_dda(t_player p, t_ray *r);
void			cast_ray(t_game *g, t_ray *r);
void			set_up_wall(t_game *g, t_ray *r);
void			draw_col(t_game *g, t_ray r, int x);

// minimap
void			render_minimap(t_game *game);

// rendering
void			render_frame(t_game *game);

// movement
void			update_movement(t_game *game);
void			cursor_hook(double xpos, double ypos, void *param);

#endif
