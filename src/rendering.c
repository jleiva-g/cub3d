/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleiva-g <jleiva-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 07:02:14 by jleiva-g          #+#    #+#             */
/*   Updated: 2026/05/18 07:02:21 by jleiva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	render_frame(void *param)
{
	t_game	*game;
	int		x;
	t_ray	ray;

	game = (t_game *) param;
	x = 0;
	while (x < WIDTH)
	{
		set_up_ray(game->player, &ray, x);
		set_up_dda(game->player, &ray);
		cast_ray(game, &ray);
		get_wall_boundaries(&ray);
		draw_col(game, ray, x);
		x++;
	}
}
