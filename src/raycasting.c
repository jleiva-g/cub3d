/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleiva-g <jleiva-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 06:59:42 by jleiva-g          #+#    #+#             */
/*   Updated: 2026/05/27 14:39:21 by jleiva-g         ###   ########.fr       */
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
	r->is_door = 0;
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
		if (g->map.grid[(int) r->cell.y][(int) r->cell.x] == 'D')
		{
			hit = 1;
			r->is_door = 1;
		}
	}
}

void	set_up_wall(t_game *g, t_ray *r)
{
	if (r->side == 0)
		r->wall_dist = r->grid_dist.x - r->cell_dist.x;
	else
		r->wall_dist = r->grid_dist.y - r->cell_dist.y;
	r->wall_height = HEIGHT / r->wall_dist;
	r->wall_start = HEIGHT / 2 - r->wall_height / 2;
	if (r->wall_start < 0)
		r->wall_start = 0;
	r->wall_end = HEIGHT / 2 + r->wall_height / 2;
	if (r->wall_end >= HEIGHT)
		r->wall_end = HEIGHT - 1;
	if (r->side == 0)
		r->wall_x = g->player.pos.y + r->wall_dist * r->ray_dir.y;
	else
		r->wall_x = g->player.pos.x + r->wall_dist * r->ray_dir.x;
	r->wall_x -= floorf(r->wall_x);
}

void	draw_col(t_game *g, t_ray r, int x)
{
	int				y;
	t_point			tex_pos;
	float			step;
	mlx_texture_t	*tex;

	tex = get_texture(g, r);
	tex_pos.x = r.wall_x * tex->width;
	if ((r.side == 0 && r.ray_dir.x < 0) || (r.side == 1 && r.ray_dir.y > 0))
		tex_pos.x = tex->width - tex_pos.x - 1;
	y = 0;
	while (y < r.wall_start)
		mlx_put_pixel(g->view, x, y++, g->map.ceil_color);
	step = (float) tex->height / r.wall_height;
	tex_pos.y = (r.wall_start - HEIGHT / 2 + r.wall_height / 2) * step;
	while (y < r.wall_end)
	{
		mlx_put_pixel(g->view, x, y++, get_pixel(tex, tex_pos.x, tex_pos.y));
		tex_pos.y += step;
	}
	while (y < HEIGHT)
		mlx_put_pixel(g->view, x, y++, g->map.floor_color);
}
