/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleiva-g <jleiva-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 20:17:27 by jleiva-g          #+#    #+#             */
/*   Updated: 2026/05/18 07:08:57 by jleiva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	big_HARDcode(t_game *game)
{
	static char *map[] = {
		"1111111111111111111111",
		"1000000000000000000001",
		"1000000010000000000001",
		"1000000001000000000001",
		"1000000000000000000001",
		"1011111110111111111101",
		"1000000010000000000101",
		"1110111011110111110101",
		"1000100000010000010101",
		"1011101110000111010101",
		"1000001000N00100010001",
		"1111101010000101111101",
		"1000101000000100000001",
		"1010101111111111111101",
		"1000100000000000000001",
		"1011111111111111111101",
		"1000000000000000000001",
		"1111111111111111111111",
		NULL
	};
	game->map.grid = map;
	game->map.ceil_color = 0x87CEEBFF;
	game->map.floor_color = 0x8B4513FF;
	game->map.height = 18;
	game->map.width = 0;
	game->player.pos.x = 10.5;
	game->player.pos.y = 10.5;
	game->player.dir.x = -1;
	game->player.dir.y = 0;
	game->player.plane.x = -game->player.dir.y * FOV;
	game->player.plane.y = game->player.dir.x * FOV;
}

int	init(t_game *game)
{
	// validate()
	// parse()
	game->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	if (!game->mlx)
		return (EXIT_FAILURE);
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img || (mlx_image_to_window(game->mlx, game->img, 0, 0) < 0))
		return (EXIT_FAILURE);
	big_HARDcode(game);
	return (EXIT_SUCCESS);
}
