/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregueir <gregueir@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 20:17:27 by jleiva-g          #+#    #+#             */
/*   Updated: 2026/06/11 13:14:00 by gregueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// Sets the name of the window to Arg[1] - maps/, so it only works if the name for the map is
// maps/XXX.cub It will crash if strlen(argv[1]) < 5 or doesnt include a .
// static void	set_wname(t_game *game, char **args)
// {
// 	int	i;

// 	i = 0;
// 	game->wname = ft_calloc((ft_strlen(args[1]) + 1), sizeof(char));
// 	if (!game->wname) //This can be condensated into a single line when we decide how to do error handling
// 	{
// 		printf("Set_wname malloc issue");
// 		return;
// 	}
// 	while (args[1][i + 5] != '.')
// 	{
// 		game->wname[i] = args[1][i + 5];
// 		i++;
// 	}
// 	i = 0;
// 	while (game->wname[i])
// 	{
// 		if (i == 0 && ft_isalpha(game->wname[i]))
// 			game->wname[i] = ft_toupper(game->wname[i]);
// 		else if (game->wname[i - 1] == '_')
// 		{
// 			if (ft_isalpha(game->wname[i]))
// 				game->wname[i] = ft_toupper(game->wname[i]);
// 			game->wname[i - 1] = ' ';
// 		}
// 		i++;
// 	}
// }

static void	init_mem(t_game *game)
{
	game->mlx = NULL;
	game->wname = NULL;
	game->view = NULL;
	game->mmap = NULL;
	game->weapon[0] = NULL;
	game->weapon[1] = NULL;
	game->weapon[2] = NULL;
	game->tex.north = NULL;
	game->tex.south = NULL;
	game->tex.east = NULL;
	game->tex.west = NULL;
	game->tex.door = NULL;
	game->tex.weapon[0] = NULL;
	game->tex.weapon[1] = NULL;
	game->tex.weapon[2] = NULL;
	game->map.grid = NULL;
	game->mouse_x = WIDTH / 2;
	game->doors = NULL;
}

static void	load_tex(t_game *game)
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
	game->tex.door = mlx_load_png("door.png");
	if (!game->tex.door)
		throw_error(game, ERR_T);
	game->tex.weapon[0] = mlx_load_png("f0.png");
	if (!game->tex.weapon[0])
		throw_error(game, ERR_T);
	game->tex.weapon[1] = mlx_load_png("f1.png");
	if (!game->tex.weapon[1])
		throw_error(game, ERR_T);
	game->tex.weapon[2] = mlx_load_png("f2.png");
	if (!game->tex.weapon[2])
		throw_error(game, ERR_T);
}

static void	tex_to_img(t_game *game)
{
	game->weapon[0] = mlx_texture_to_image(game->mlx, game->tex.weapon[0]);
	if (!game->weapon[0]
		|| (mlx_image_to_window(game->mlx, game->weapon[0], 0, 0) < 0))
		throw_error(game, ERR_I);
	game->weapon[1] = mlx_texture_to_image(game->mlx, game->tex.weapon[1]);
	if (!game->weapon[1]
		|| (mlx_image_to_window(game->mlx, game->weapon[1], 0, 0) < 0))
		throw_error(game, ERR_I);
	game->weapon[2] = mlx_texture_to_image(game->mlx, game->tex.weapon[2]);
	if (!game->weapon[2]
		|| (mlx_image_to_window(game->mlx, game->weapon[2], 0, 0) < 0))
		throw_error(game, ERR_I);
	game->weapon[1]->enabled = false;
	game->weapon[2]->enabled = false;
}

static void	init_mlx(t_game *game)
{
	game->mlx = mlx_init(WIDTH, HEIGHT, game->wname, true);
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

void	init(t_game *game, char **argv)
{
	init_mem(game);
	game->map.check_map = 0;
	game->map.width = 0;
	if (validate(game, argv) < 0)
		throw_error(game, ERR_X);
	if (parse(game, argv) < 0)
		throw_error(game, ERR_X);
	exit(EXIT_SUCCESS);
	// if (argv[1])
	// 	set_wname(game, argv);
	init_mlx(game);
}
