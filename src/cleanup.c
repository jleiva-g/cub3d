/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleiva-g <jleiva-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 20:27:20 by jleiva-g          #+#    #+#             */
/*   Updated: 2026/06/12 15:24:48 by jleiva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	free_tex(t_tex tex)
{
	free(tex.north_path);
	free(tex.south_path);
	free(tex.west_path);
	free(tex.east_path);
	if (tex.north)
		mlx_delete_texture(tex.north);
	if (tex.south)
		mlx_delete_texture(tex.south);
	if (tex.west)
		mlx_delete_texture(tex.west);
	if (tex.east)
		mlx_delete_texture(tex.east);
	if (tex.weapon[0])
		mlx_delete_texture(tex.weapon[0]);
	if (tex.weapon[1])
		mlx_delete_texture(tex.weapon[1]);
	if (tex.weapon[2])
		mlx_delete_texture(tex.weapon[2]);
}

void	cleanup(t_game *game)
{
	free(game->wname);
	if (game->view)
		mlx_delete_image(game->mlx, game->view);
	if (game->mmap)
		mlx_delete_image(game->mlx, game->mmap);
	if (game->weapon[0])
		mlx_delete_image(game->mlx, game->weapon[0]);
	if (game->weapon[1])
		mlx_delete_image(game->mlx, game->weapon[1]);
	if (game->weapon[2])
		mlx_delete_image(game->mlx, game->weapon[2]);
	free_tex(game->tex);
	free_split(game->map.grid);
	free(game->doors);
	if (game->mlx)
		mlx_terminate(game->mlx);
}

void	throw_error(t_game *game, char *err_msg)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(err_msg, 2);
	cleanup(game);
	exit(EXIT_FAILURE);
}
