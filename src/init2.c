/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleiva-g <jleiva-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 16:59:55 by gregueir          #+#    #+#             */
/*   Updated: 2026/07/06 14:57:57 by jleiva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_mlx(t_game *game)
{
	game->mlx = mlx_init(WIDTH, HEIGHT, game->wname, false);
	if (!game->mlx)
		throw_error(game, ERR_X);
	game->view = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->view || (mlx_image_to_window(game->mlx, game->view, 0, 0) < 0))
		throw_error(game, ERR_I);
	game->mmap = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->mmap || (mlx_image_to_window(game->mlx, game->mmap, 0, 0) < 0))
		throw_error(game, ERR_I);
	load_tex(game);
	tex_to_img(game);
}

void	init_map(t_game *game)
{
	int	i;

	game->map.grid = ft_calloc(game->map.height + 1, sizeof(char *));
	if (!game->map.grid)
		throw_error(game, ERR_M);
	i = 0;
	while (i < game->map.height)
	{
		game->map.grid[i] = malloc((game->map.width + 1) * sizeof(char));
		if (!game->map.grid[i])
			throw_error(game, ERR_M);
		i++;
	}
}
