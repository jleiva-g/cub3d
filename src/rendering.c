/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleiva-g <jleiva-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 07:02:14 by jleiva-g          #+#    #+#             */
/*   Updated: 2026/05/20 14:13:38 by jleiva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	render_view(t_game *game)
{
	int		x;
	t_ray	ray;

	ft_bzero(game->img->pixels, WIDTH * HEIGHT * sizeof(int32_t));
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

void	render_frame(t_game *game)
{
	render_view(game);
}
