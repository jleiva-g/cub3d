/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregueir <gregueir@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 14:13:13 by gregueir          #+#    #+#             */
/*   Updated: 2026/06/15 16:53:19 by gregueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static	char	*extract_path(char *line)
{
	char	**str;
	char	*out;

	str = ft_split(line, ' ');
	if (!ft_strnstr(str[1], ".png", ft_strlen(str[1])))
	{
		free_split(str);
		return (NULL);
	}
	out = ft_strdup(str[1]);
	free_split(str);
	return (out);
}
static	int load_textures_ew(t_game *game, char *line, char c)
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

static	int load_textures_ns(t_game *game, char *line, char c)
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

static	int	load_textures(t_game *game, char *line, int key[6])
{
	int	size;

	size = ft_strlen(line);
	if (size <= 1 || is_empty(line, size))
		return (0);
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
	return (0);
}

int	parse(t_game *game, char **argv)
{
	char	*line;
	int		key[6];
	int		fd;

	ft_bzero(key, sizeof(key));
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		throw_error(game, ERR_R);
	line = get_next_line(fd);
	while (line)
	{
		if (check_key(key))
			load_textures(game, line, key);
		/*else
			load_map();*/
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
