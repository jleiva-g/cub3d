/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleiva-g <jleiva-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 06:59:42 by jleiva-g          #+#    #+#             */
/*   Updated: 2026/05/18 07:05:36 by jleiva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	set_up_ray(t_player p, t_ray *r, int x)
{
	float	col_factor;

	col_factor = 2.0f * x / WIDTH - 1.0f;
	r->ray_dir.x = p.dir.x + p.plane.x * col_factor;
	r->ray_dir.y = p.dir.y + p.plane.y * col_factor;
	r->cell.x = (int) p.pos.x;
	r->cell.y = (int) p.pos.y;
	if (r->ray_dir.x == 0)
		r->cell_dist.x = FLT_MAX;
	else
		r->cell_dist.x = fabsf(1.0f / r->ray_dir.x);
	if (r->ray_dir.y == 0)
		r->cell_dist.y = FLT_MAX;
	else
		r->cell_dist.y = fabsf(1.0f / r->ray_dir.y);
	r->side = 0;
}

void	set_up_dda(t_player p, t_ray *r)
{
	if (r->ray_dir.x < 0)
	{
		r->step.x = -1;
		r->grid_dist.x = (p.pos.x - r->cell.x) * r->cell_dist.x;
	}
	else
	{
		r->step.x = 1;
		r->grid_dist.x = (r->cell.x + 1.0f - p.pos.x) * r->cell_dist.x;
	}
	if (r->ray_dir.y < 0)
	{
		r->step.y = -1;
		r->grid_dist.y = (p.pos.y - r->cell.y) * r->cell_dist.y;
	}
	else
	{
		r->step.y = 1;
		r->grid_dist.y = (r->cell.y + 1.0f - p.pos.y) * r->cell_dist.y;
	}
}

void	cast_ray(t_game *g, t_ray *r)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (r->grid_dist.x < r->grid_dist.y)
		{
			r->grid_dist.x += r->cell_dist.x;
			r->cell.x += r->step.x;
			r->side = 0;
		}
		else
		{
			r->grid_dist.y += r->cell_dist.y;
			r->cell.y += r->step.y;
			r->side = 1;
		}
		if (g->map.grid[(int) r->cell.y][(int) r->cell.x] == '1')
			hit = 1;
	}
}

void	get_wall_boundaries(t_ray *r)
{
	float	wall_dist;
	int		wall_height;

	if (r->side == 0)
		wall_dist = r->grid_dist.x - r->cell_dist.x;
	else
		wall_dist = r->grid_dist.y - r->cell_dist.y;
	wall_height = HEIGHT / wall_dist;
	r->wall_start = -wall_height / 2 + HEIGHT / 2;
	if (r->wall_start < 0)
		r->wall_start = 0;
	r->wall_end = wall_height / 2 + HEIGHT / 2;
	if (r->wall_end >= HEIGHT)
		r->wall_end = HEIGHT - 1;
}

void	draw_col(t_game *g, t_ray r, int x)
{
	int	y;

	y = 0;
	while (y < r.wall_start)
		mlx_put_pixel(g->img, x, y++, g->map.ceil_color);
	while (y < r.wall_end)
	{
		if (r.side == 0 && r.ray_dir.x > 0)
			mlx_put_pixel(g->img, x, y++, 0x7CFC00FF);
		else if (r.side == 0)
			mlx_put_pixel(g->img, x, y++, 0x556B2FFF);
		else if (r.ray_dir.y > 0)
			mlx_put_pixel(g->img, x, y++, 0x228B22FF);
		else
			mlx_put_pixel(g->img, x, y++, 0x2E8B57FF);
	}
	while (y < HEIGHT)
		mlx_put_pixel(g->img, x, y++, g->map.floor_color);
}
