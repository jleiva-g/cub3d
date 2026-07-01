/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregueir <gregueir@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 20:17:27 by jleiva-g          #+#    #+#             */
/*   Updated: 2026/07/01 15:28:52 by gregueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	set_wname(t_game *game, char **args)
{
	int	i;

	i = 0;
	game->wname = ft_calloc((ft_strlen(args[1]) + 1), sizeof(char));
	if (!game->wname)
		throw_error(game, ERR_M);
	while (args[1][i + 5] && args[1][i + 5] != '.')
	{
		game->wname[i] = args[1][i + 5];
		i++;
	}
	i = 0;
	while (game->wname[i])
	{
		if (i == 0 && ft_isalpha(game->wname[i]))
			game->wname[i] = ft_toupper(game->wname[i]);
		else if (game->wname[i - 1] == '_')
		{
			if (ft_isalpha(game->wname[i]))
				game->wname[i] = ft_toupper(game->wname[i]);
			game->wname[i - 1] = ' ';
		}
		i++;
	}
}

static void	init_mem(t_game *game)
{
	game->mlx = NULL;
	game->wname = NULL;
	game->view = NULL;
	game->map.height = 0;
	game->mmap = NULL;
	game->weapon[0] = NULL;
	game->weapon[1] = NULL;
	game->weapon[2] = NULL;
	game->tex.north_path = NULL;
	game->tex.south_path = NULL;
	game->tex.west_path = NULL;
	game->tex.east_path = NULL;
	game->tex.north = NULL;
	game->tex.south = NULL;
	game->tex.west = NULL;
	game->tex.east = NULL;
	game->tex.door = NULL;
	game->tex.weapon[0] = NULL;
	game->tex.weapon[1] = NULL;
	game->tex.weapon[2] = NULL;
	game->map.grid = NULL;
	game->mouse_x = WIDTH / 2;
	game->doors = NULL;
	game->player.dir.x = 0;
	game->player.dir.y = 0;
}

void	load_tex(t_game *game)
{
	game->tex.north = mlx_load_png(game->tex.north_path);
	if (!game->tex.north)
		throw_error(game, ERR_T);
	game->tex.south = mlx_load_png(game->tex.south_path);
	if (!game->tex.south)
		throw_error(game, ERR_T);
	game->tex.west = mlx_load_png(game->tex.west_path);
	if (!game->tex.west)
		throw_error(game, ERR_T);
	game->tex.east = mlx_load_png(game->tex.east_path);
	if (!game->tex.east)
		throw_error(game, ERR_T);
	game->tex.door = mlx_load_png("tex/door.png");
	if (!game->tex.door)
		throw_error(game, ERR_T);
	game->tex.weapon[0] = mlx_load_png("tex/f0.png");
	if (!game->tex.weapon[0])
		throw_error(game, ERR_T);
	game->tex.weapon[1] = mlx_load_png("tex/f1.png");
	if (!game->tex.weapon[1])
		throw_error(game, ERR_T);
	game->tex.weapon[2] = mlx_load_png("tex/f2.png");
	if (!game->tex.weapon[2])
		throw_error(game, ERR_T);
}

void	tex_to_img(t_game *game)
{
	int	x;
	int	y;

	x = WIDTH / 2 - game->tex.weapon[0]->width / 2;
	y = HEIGHT - game->tex.weapon[0]->height;
	game->weapon[0] = mlx_texture_to_image(game->mlx, game->tex.weapon[0]);
	if (!game->weapon[0]
		|| (mlx_image_to_window(game->mlx, game->weapon[0], x, y) < 0))
		throw_error(game, ERR_I);
	game->weapon[1] = mlx_texture_to_image(game->mlx, game->tex.weapon[1]);
	if (!game->weapon[1]
		|| (mlx_image_to_window(game->mlx, game->weapon[1], x, y) < 0))
		throw_error(game, ERR_I);
	game->weapon[2] = mlx_texture_to_image(game->mlx, game->tex.weapon[2]);
	if (!game->weapon[2]
		|| (mlx_image_to_window(game->mlx, game->weapon[2], x, y) < 0))
		throw_error(game, ERR_I);
	game->weapon[1]->enabled = false;
	game->weapon[2]->enabled = false;
}

void	init(t_game *game, char **argv)
{
	init_mem(game);
	game->map.check_map = 0;
	game->map.check_player = 0;
	game->map.check_door = 0;
	game->map.width = 0;
	if (validate(game, argv) < 0)
		throw_error(game, ERR_X);
	if (game->map.check_player != 1)
		throw_error(game, ERR_Y);
	if (game->map.check_door > 0)
	{
		game->doors = malloc((game->map.check_door + 1) * sizeof(t_point));
		if (!game->doors)
			throw_error(game, ERR_M);
		game->doors[game->map.check_door].x = -1;
		game->doors[game->map.check_door].y = -1;
	}
	if (parse(game, argv) < 0)
		throw_error(game, ERR_X);
	clean_path(game);
	set_wname(game, argv);
	init_mlx(game);
}
