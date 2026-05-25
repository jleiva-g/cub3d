/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleiva-g <jleiva-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 07:02:14 by jleiva-g          #+#    #+#             */
/*   Updated: 2026/05/25 06:42:33 by jleiva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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

void	render_frame(t_game *game)
{
	render_view(game);
	render_minimap(game);
}
