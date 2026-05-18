/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleiva-g <jleiva-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 18:47:11 by jleiva-g          #+#    #+#             */
/*   Updated: 2026/05/18 19:06:48 by jleiva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	game_loop(void *param)
{
	update_movement(param);
	render_frame(param);
}

void	keyhook(mlx_key_data_t keydata, void *param)
{
	if (keydata.action == MLX_PRESS && keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(param);
}

int	main(int argc, char **argv)
{
	t_game	game;

	(void) argc;
	(void) argv;
	if (init(&game))
		return (EXIT_FAILURE);
	mlx_loop_hook(game.mlx, &game_loop, &game);
	mlx_key_hook(game.mlx, &keyhook, game.mlx);
	mlx_loop(game.mlx);
	cleanup(game);
	return (EXIT_SUCCESS);
}
