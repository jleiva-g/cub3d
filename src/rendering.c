/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleiva-g <jleiva-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 07:02:14 by jleiva-g          #+#    #+#             */
/*   Updated: 2026/06/03 21:10:33 by jleiva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	check_doors(t_game *game)
{
	int	i;
	int	px;
	int	py;
	int	dx;
	int	dy;

	i = 0;
	px = game->player.pos.x;
	py = game->player.pos.y;
	while (game->doors[i].x > -1)
	{
		dx = game->doors[i].x;
		dy = game->doors[i].y;
		if (abs(px - dx) <= 1 && abs(py - dy) <= 1)
			game->map.grid[dy][dx] = '0';
		else
			game->map.grid[dy][dx] = 'D';
		i++;
	}
}

static void	render_view(t_game *game)
{
	int		x;
	t_ray	ray;

	x = 0;
	while (x < WIDTH)
	{
		set_up_ray(game->player, &ray, x);
		set_up_dda(game->player, &ray);
		cast_ray(game, &ray);
		set_up_wall(game, &ray);
		draw_col(game, ray, x);
		x++;
	}
}

static void	render_weapon(t_game *game)
{
	static int	animation = 0;
	static int	frame = 0;
	static int	start_frame;

	if (mlx_is_mouse_down(game->mlx, MLX_MOUSE_BUTTON_LEFT) && !animation)
	{
		animation = 1;
		start_frame = frame;
	}
	if (animation && frame - start_frame == 0)
		game->weapon[1]->enabled = true;
	if (animation && frame - start_frame == 6)
	{
		game->weapon[2]->enabled = true;
		game->weapon[1]->enabled = false;
	}
	if (animation && frame - start_frame == 18)
	{
		game->weapon[2]->enabled = false;
		animation = 0;
	}
	if (animation)
		frame++;
}

void	render_frame(t_game *game)
{
	if (game->doors)
		check_doors(game);
	render_view(game);
	render_weapon(game);
	render_minimap(game);
}
