/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregueir <gregueir@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 13:05:04 by gregueir          #+#    #+#             */
/*   Updated: 2026/06/04 13:18:03 by gregueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	check_key(int key[6])
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
	close(fd);
	return (0);
}