/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleiva-g <jleiva-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 07:03:46 by jleiva-g          #+#    #+#             */
/*   Updated: 2026/06/26 13:45:12 by jleiva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d_bonus.h"

static void	rotate(t_player *p, float speed)
{
	float	old_dir_x;

	old_dir_x = p->dir.x;
	p->dir.x = p->dir.x * cosf(speed) - p->dir.y * sinf(speed);
	p->dir.y = old_dir_x * sinf(speed) + p->dir.y * cosf(speed);
	p->plane.x = -p->dir.y * FOV;
	p->plane.y = p->dir.x * FOV;
}

static void	move(t_game *g, int strafe, float speed)
{
	t_point	new_pos;

	if (strafe)
	{
		new_pos.x = g->player.pos.x + g->player.plane.x * speed;
		new_pos.y = g->player.pos.y + g->player.plane.y * speed;
	}
	else
	{
		new_pos.x = g->player.pos.x + g->player.dir.x * speed;
		new_pos.y = g->player.pos.y + g->player.dir.y * speed;
	}
	if (g->map.grid[(int) g->player.pos.y][(int) new_pos.x] != '1'
		&& g->map.grid[(int) g->player.pos.y][(int) new_pos.x] != 'D')
		g->player.pos.x = new_pos.x;
	if (g->map.grid[(int) new_pos.y][(int) g->player.pos.x] != '1'
		&& g->map.grid[(int) new_pos.y][(int) g->player.pos.x] != 'D')
		g->player.pos.y = new_pos.y;
}

void	update_movement(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		move(game, 0, MOVE_SPEED);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		move(game, 0, -MOVE_SPEED);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		move(game, 1, MOVE_SPEED);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		move(game, 1, -MOVE_SPEED);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		rotate(&game->player, -ROTATE_SPEED);
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		rotate(&game->player, ROTATE_SPEED);
	rotate(&game->player, game->mouse_delta * 0.002f);
	game->mouse_delta *= 0.75f;
}

void	cursor_hook(double x, double y, void *param)
{
	t_game	*game;

	(void) y;
	game = param;
	game->mouse_delta = x - game->mouse_x;
	game->mouse_x = x;
}
