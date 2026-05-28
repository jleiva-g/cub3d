/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregueir <gregueir@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 20:27:20 by jleiva-g          #+#    #+#             */
/*   Updated: 2026/05/27 15:43:36 by gregueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	cleanup(t_game game)
{
	//mlx_delete_image(game.mlx, game.img);
	mlx_terminate(game.mlx);
}
