/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregueir <gregueir@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 20:17:27 by jleiva-g          #+#    #+#             */
/*   Updated: 2026/06/01 17:12:17 by gregueir         ###   ########.fr       */
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

static	int	check_key(int key[6])
{
	int i;

	i = 0;
	while (i < 6)
	{
		if (!key[i])
			return (1);
		i++;
	}
	return (0);
}

//I need a flag for "We've started checking the map and now empty lines are not admissible"
int	validate(t_game *game, char **argv)
{
	char	*line;
	int		err;
	int		key[6];
	int		fd;

	ft_bzero(key, sizeof(key));
	err = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (EXIT_FAILURE);
	line = get_next_line(fd);
	while (line)
	{
		if (check_key(key))
			err = validate_line(line, key);
		else
			err = validate_map(game, line);
		free(line);
		if (err)
			return(printf("Something wrong on validation"), EXIT_FAILURE);
		line = get_next_line(fd);
	}
	free(line);
	return (0);
}

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

int	init(t_game *game, char **argv)
{
	(void)argv;

	if (validate(game, argv) < 0)
		exit(EXIT_FAILURE);
	//exit(EXIT_SUCCESS);
	// parse()
	// if (argv[1])
	// 	set_wname(game, argv);
	exit (EXIT_SUCCESS);
	game->mlx = mlx_init(WIDTH, HEIGHT, game->wname, true);
	if (!game->mlx)
		return (EXIT_FAILURE);
	game->view = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->view || (mlx_image_to_window(game->mlx, game->view, 0, 0) < 0))
		return (EXIT_FAILURE);
	game->mmap = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->mmap || (mlx_image_to_window(game->mlx, game->mmap, 0, 0) < 0))
		return (EXIT_FAILURE);
	big_HARDcode(game);
	return (EXIT_SUCCESS);
}
