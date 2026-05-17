/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleiva-g <jleiva-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 20:17:27 by jleiva-g          #+#    #+#             */
/*   Updated: 2026/05/17 23:57:46 by jleiva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// rayDir = dir + plane * cameraX
void	init_ray(t_game *g, t_ray *r, int x)
{
	r->camera_x = 2.0f * x / (float) WIDTH - 1.0f;
	r->ray_dir_x = g->player.dir_x
		+ g->player.plane_x * r->camera_x;
	r->ray_dir_y = g->player.dir_y
		+ g->player.plane_y * r->camera_x;
	r->map_x = (int) g->player.x;
	r->map_y = (int) g->player.y;
	if (r->ray_dir_x == 0)
		r->delta_dist_x = FLT_MAX;
	else
		r->delta_dist_x = fabsf(1.0f / r->ray_dir_x);
	if (r->ray_dir_y == 0)
		r->delta_dist_y = FLT_MAX;
	else
		r->delta_dist_y = fabsf(1.0f / r->ray_dir_y);
	r->hit = 0;
}

void	init_dda(t_game *g, t_ray *r)
{
	if (r->ray_dir_x < 0)
	{
		r->step_x = -1;
		r->side_dist_x = (g->player.x - r->map_x) * r->delta_dist_x;
	}
	else
	{
		r->step_x = 1;
		r->side_dist_x = (r->map_x + 1.0f - g->player.x)
			* r->delta_dist_x;
	}
	if (r->ray_dir_y < 0)
	{
		r->step_y = -1;
		r->side_dist_y = (g->player.y - r->map_y) * r->delta_dist_y;
	}
	else
	{
		r->step_y = 1;
		r->side_dist_y = (r->map_y + 1.0f - g->player.y)
			* r->delta_dist_y;
	}
}

void	perform_dda(t_game *g, t_ray *r)
{
	while (!r->hit)
	{
		if (r->side_dist_x < r->side_dist_y)
		{
			r->side_dist_x += r->delta_dist_x;
			r->map_x += r->step_x;
			r->side = 0;
		}
		else
		{
			r->side_dist_y += r->delta_dist_y;
			r->map_y += r->step_y;
			r->side = 1;
		}
		if (g->map.grid[r->map_y][r->map_x] == '1')
			r->hit = 1;
	}
}

// lineHeight = screenHeight ​/ perpWallDist
void	calc_wall(t_ray *r)
{
	if (r->side == 0)
		r->perp_wall_dist = r->side_dist_x - r->delta_dist_x;
	else
		r->perp_wall_dist = r->side_dist_y - r->delta_dist_y;
	r->line_height = (int)(HEIGHT / r->perp_wall_dist);
	r->draw_start = -r->line_height / 2 + HEIGHT / 2;
	if (r->draw_start < 0)
		r->draw_start = 0;
	r->draw_end = r->line_height / 2 + HEIGHT / 2;
	if (r->draw_end >= HEIGHT)
		r->draw_end = HEIGHT - 1;
}

void	draw_column(t_game *g, t_ray *r, int x)
{
	int	y;

	y = 0;
	while (y < r->draw_start)
		mlx_put_pixel(g->img, x, y++, g->map.ceil_color);
	while (y < r->draw_end)
	{
		if (r->side == 0)
		{
			if (r->ray_dir_x > 0)
				mlx_put_pixel(g->img, x, y++, 0x556B2FFF);
			else
				mlx_put_pixel(g->img, x, y++, 0x7CFC00FF);
		}
		else if (r->ray_dir_y > 0)
			mlx_put_pixel(g->img, x, y++, 0x2E8B57FF);
		else
			mlx_put_pixel(g->img, x, y++, 0x228B22FF);
	}
	while (y < HEIGHT)
		mlx_put_pixel(g->img, x, y++, g->map.floor_color);
}

void	render_frame(t_game *game)
{
	int		x;
	t_ray	ray;

	x = 0;
	while (x < WIDTH)
	{
		init_ray(game, &ray, x);
		init_dda(game, &ray);
		perform_dda(game, &ray);
		calc_wall(&ray);
		draw_column(game, &ray, x);
		x++;
	}
}

int	init(t_game *game)
{
	game->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	if (!game->mlx)
		return (EXIT_FAILURE);
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img || (mlx_image_to_window(game->mlx, game->img, 0, 0) < 0))
		return (EXIT_FAILURE);
	char *map[] = {
		"1111111111111111111111",
		"1000000000000000000001",
		"1000000000000000000001",
		"1000000000000000000001",
		"1000000000000000000001",
		"1011111110111111111101",
		"1000000010000000000101",
		"1110111011110111110101",
		"1000100000010000010101",
		"1011101110000111010101",
		"1000001000N00100010001",
		"1111101010000101111101",
		"1000101000000100000001",
		"1010101111111111111101",
		"1000100000000000000001",
		"1011111111111111111101",
		"1000000000000000000001",
		"111111111111111111111",
		NULL
	};
	game->map.grid = map;
	game->map.ceil_color = 0x87CEEBFF;
	game->map.floor_color = 0x8B4513FF;
	game->player.x = 10.5;
	game->player.y = 10.5;
	game->player.dir_x = -1;
	game->player.dir_y = 0;
	game->player.plane_x = -game->player.dir_y * 0.66f;
	game->player.plane_y = game->player.dir_x * 0.66f;
	render_frame(game);
	return (EXIT_SUCCESS);
}
