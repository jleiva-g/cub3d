/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleiva-g <jleiva-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 18:46:53 by jleiva-g          #+#    #+#             */
/*   Updated: 2026/05/18 07:04:52 by jleiva-g         ###   ########.fr       */
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
# define ROTATE_SPEED 0.05f
# define MOVE_SPEED 0.1f

typedef struct s_point
{
	float	x;
	float	y;
}	t_point;

typedef struct s_img
{
	void	*img;
	char	*path;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_tex
{
	t_img	north;
	t_img	south;
	t_img	west;
	t_img	east;
	t_img	door;
	t_img	*weapon;
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
	void		*win;
	void		*img;
	t_map		map;
	t_player	player;
	t_tex		tex;
}	t_game;

typedef struct s_ray
{
	t_point	ray_dir;
	t_point	cell;
	t_point	cell_dist;
	t_point	grid_dist;
	t_point	step;
	int		side;
	int		wall_start;
	int		wall_end;
}	t_ray;

// cleanup
void	cleanup(t_game game);

// init
int		init(t_game *game);
void	render_frame(void *param);
void	rotate_right(t_player *p);

// raycasting
void	set_up_ray(t_player p, t_ray *r, int x);
void	set_up_dda(t_player p, t_ray *r);
void	cast_ray(t_game *g, t_ray *r);
void	get_wall_boundaries(t_ray *r);
void	draw_col(t_game *g, t_ray r, int x);

// rendering
void	render_frame(void *param);

// movement
void	keyhook(mlx_key_data_t keydata, void *param);

#endif
