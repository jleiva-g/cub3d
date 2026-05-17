/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleiva-g <jleiva-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 18:47:11 by jleiva-g          #+#    #+#             */
/*   Updated: 2026/05/17 16:52:14 by jleiva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	keyhook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *) param;
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		// manage_keypress(keydata, game);
		// ft_memset(game->img->pixels, 0, WIDTH * HEIGHT * sizeof(int));
		// draw_map(*game);
		if (keydata.key == MLX_KEY_ESCAPE)
			mlx_close_window(game->mlx);
	}
}

int	main(int argc, char **argv)
{
	t_game	game;

	(void) argc;
	(void) argv;
	if (init(&game))
		return (EXIT_FAILURE);
	mlx_key_hook(game.mlx, &keyhook, &game);
	mlx_loop(game.mlx);
	cleanup(game);
	return (EXIT_SUCCESS);
}
