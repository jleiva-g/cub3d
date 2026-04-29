/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleiva-g <jleiva-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 18:47:11 by jleiva-g          #+#    #+#             */
/*   Updated: 2026/05/01 20:40:11 by jleiva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	(void) argc;
	(void) argv;
	if (init(&game))
		return (EXIT_FAILURE);
	mlx_loop(game.mlx);
	cleanup(game);
	return (EXIT_SUCCESS);
}
