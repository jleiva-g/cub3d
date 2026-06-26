/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleiva-g <jleiva-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 18:47:11 by jleiva-g          #+#    #+#             */
/*   Updated: 2026/06/26 13:15:44 by jleiva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	game_loop(void *param)
{
	update_movement(param);
	render_frame(param);
}

static void	keyhook(mlx_key_data_t keydata, void *param)
{
	static int	mouse_cap = 1;

	if (keydata.action == MLX_PRESS && keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(param);
	if (keydata.action == MLX_PRESS && keydata.key == MLX_KEY_P)
	{
		if (mouse_cap)
		{
			mlx_set_cursor_mode(param, MLX_MOUSE_NORMAL);
			mouse_cap = 0;
		}
		else
		{
			mlx_set_cursor_mode(param, MLX_MOUSE_DISABLED);
			mouse_cap = 1;
		}
	}
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		ft_putendl_fd("Please introduce a valid *.cub map file\n", 2);
		return (EXIT_FAILURE);
	}
	ft_bzero(&game, sizeof(t_game));
	init(&game, argv);
	mlx_loop_hook(game.mlx, &game_loop, &game);
	mlx_key_hook(game.mlx, &keyhook, game.mlx);
	mlx_cursor_hook(game.mlx, &cursor_hook, &game);
	mlx_set_cursor_mode(game.mlx, MLX_MOUSE_DISABLED);
	mlx_loop(game.mlx);
	cleanup(&game);
	return (EXIT_SUCCESS);
}
