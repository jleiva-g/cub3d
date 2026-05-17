/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleiva-g <jleiva-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 18:46:53 by jleiva-g          #+#    #+#             */
/*   Updated: 2026/05/17 23:52:53 by jleiva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/inc/libft.h"
# include "MLX42/include/MLX42/MLX42.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <sys/time.h>
# include <math.h>
# include <limits.h>
# include <float.h>

# define WIDTH 1920
# define HEIGHT 1080
# define FOV 0.66f

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
	float	x;
	float	y;
	float	dir_x;
	float	dir_y;
	float	plane_x;
	float	plane_y;
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
	float	camera_x;
	float	ray_dir_x;
	float	ray_dir_y;
	int		map_x;
	int		map_y;
	float	delta_dist_x;
	float	delta_dist_y;
	float	side_dist_x;
	float	side_dist_y;
	float	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_ray;

// cleanup
void	cleanup(t_game game);

// init
int		init(t_game *game);

#endif
