/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregueir <gregueir@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 14:13:13 by gregueir          #+#    #+#             */
/*   Updated: 2026/06/10 16:53:26 by gregueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static	char	*extract_path(char *line)
{
	char	*str;
	char	*out;

	str = ft_strnstr(line, " ", ft_strlen(line));
	while (*str == ' ')
		str++;
	out = ft_strdup(str);
	if (!out)
		return (ft_printf("Dup error"), NULL);
	return (out);
}

static	int	load_textures(t_game *game, char *line, int key[6])
{
	int	size;

	size = ft_strlen(line);
	if (size <= 1 || is_empty(line, size))
		return (0);
	if (ft_strnstr(line, "NO ", size))
	{
		if (!game->tex.north_path)
			game->tex.north_path = extract_path(line);
		if (game->tex.north_path)
			key[NO] = 1;
		else
			return (ft_printf("Error during tex NO"), EXIT_FAILURE);
		if (game->tex.north_path)
			ft_printf("NO is %s\n", game->tex.north_path);
	}
	return (0);
}

int	parse(t_game *game, char **argv)
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
			err = load_textures(game, line, key);
		/*else
			err = load_map();*/
		free(line);
		if (err)
			return(printf("Something wrong on parsing"), EXIT_FAILURE);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
