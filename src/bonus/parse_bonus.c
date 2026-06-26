/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleiva-g <jleiva-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 14:13:13 by gregueir          #+#    #+#             */
/*   Updated: 2026/06/26 13:45:15 by jleiva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d_bonus.h"

static	int	load_textures_ew(t_game *game, char *line, char c)
{
	if (c == 'E')
	{
		if (!game->tex.east_path)
			game->tex.east_path = extract_path(line);
		if (!game->tex.east_path)
		{
			free(line);
			throw_error(game, ERR_P);
		}
	}
	else if (c == 'W')
	{
		if (!game->tex.west_path)
			game->tex.west_path = extract_path(line);
		if (!game->tex.west_path)
		{
			free(line);
			throw_error(game, ERR_P);
		}
	}
	return (0);
}

static	int	load_textures_ns(t_game *game, char *line, char c)
{
	if (c == 'N')
	{
		if (!game->tex.north_path)
			game->tex.north_path = extract_path(line);
		if (!game->tex.north_path)
		{
			free(line);
			throw_error(game, ERR_P);
		}
	}
	else if (c == 'S')
	{
		if (!game->tex.south_path)
			game->tex.south_path = extract_path(line);
		if (!game->tex.south_path)
		{
			free(line);
			throw_error(game, ERR_P);
		}
	}
	return (0);
}

static	void	load_textures_aux(t_game *game, char *line, int key[6],
		int size)
{
	if (ft_strnstr(line, "EA ", size))
	{
		load_textures_ew(game, line, 'E');
		key[EA] = 1;
	}
	else if (ft_strnstr(line, "F ", size))
	{
		game->map.floor_color = extract_color(line);
		key[F] = 1;
		if (game->map.floor_color == -1)
		{
			free(line);
			throw_error(game, ERR_C);
		}
	}
	else if (ft_strnstr(line, "C ", size))
	{
		game->map.ceil_color = extract_color(line);
		key[C] = 1;
		if (game->map.ceil_color == -1)
		{
			free(line);
			throw_error(game, ERR_C);
		}
	}
}

static	void	load_textures(t_game *game, char *line, int key[6])
{
	int	size;

	size = ft_strlen(line);
	if (size <= 1 || is_empty(line, size))
		return ;
	if (ft_strnstr(line, "NO ", size))
	{
		load_textures_ns(game, line, 'N');
		key[NO] = 1;
	}
	else if (ft_strnstr(line, "SO ", size))
	{
		load_textures_ns(game, line, 'S');
		key[SO] = 1;
	}
	else if (ft_strnstr(line, "WE ", size))
	{
		load_textures_ew(game, line, 'W');
		key[WE] = 1;
	}
	else
		load_textures_aux(game, line, key, size);
}

int	parse(t_game *game, char **argv)
{
	char	*line;
	int		key[6];
	int		fd;

	ft_bzero(key, sizeof(key));
	init_map(game);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		throw_error(game, ERR_R);
	line = get_next_line(fd);
	while (line)
	{
		if (check_key(key))
			load_textures(game, line, key);
		else
			load_map(game, line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
