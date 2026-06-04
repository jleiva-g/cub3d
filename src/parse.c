/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregueir <gregueir@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 14:13:13 by gregueir          #+#    #+#             */
/*   Updated: 2026/06/04 13:27:43 by gregueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static	int	load_textures(t_game *game, char *line)
{
	int	size;

	size = ft_strlen(line);
	if (size <= 1 || is_empty(line, size))
		return (0);
	if (ft_strnstr(line, "NO ", size) && !key[NO])
		key[NO] = 1;
	else if (ft_strnstr(line, "NO ", size) && key[NO])
		return(printf("We need to exit here 1"), -1);
	else if (ft_strnstr(line, "SO ", size) && !key[SO])
		key[SO] = 1;
	else if (ft_strnstr(line, "SO ", size) && key[NO])
		return(printf("We need to exit here 2"), -1);
	else if (ft_strnstr(line, "EA ", size) && !key[EA])
		key[EA] = 1;
	else if (ft_strnstr(line, "EA ", size) && key[NO])
		return(printf("We need to exit here 3"), -1);
	else if (ft_strnstr(line, "WE ", size) && !key[WE])
		key[WE] = 1;
	else if (ft_strnstr(line, "WE ", size) && key[NO])
		return(printf("We need to exit here 4"), -1);
	else
		return(validate_line_aux(line, size, key));
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
			err = load_textures(game, line);
		else
			err = load_map();
		free(line);
		if (err)
			return(printf("Something wrong on parsing"), EXIT_FAILURE);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
