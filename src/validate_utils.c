/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregueir <gregueir@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 12:35:36 by gregueir          #+#    #+#             */
/*   Updated: 2026/05/28 17:58:07 by gregueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static	int	validate_line_aux(t_game *game, char *line, int size)
{
	if (ft_strnstr(line, "F ", size) && !game->key[NO])
		game->key[NO] = 1;
	else if (ft_strnstr(line, "F ", size) && game->key[NO])
		return(printf("We need to exit here"));
	else if (ft_strnstr(line, "C ", size) && !game->key[NO])
		game->key[NO] = 1;
	else if (ft_strnstr(line, "C ", size) && game->key[NO])
		return(printf("We need to exit here"));
	else
		return(0);
}

//I dont like this
static	int	is_empty(char *line, int size)
{
	int	i;

	i = 0;
	while(line[i] && i < size)
	{
		if (line[i] == " " || line[i] == "\n")
			i++;
		else
			return (0);
	}
	return (1);
}

int	validate_line(t_game *game, char *line)
{
	int	size;

	size = ft_strlen(line);
	if (size > 1 && is_empty(line, size))
		return (printf("Wrong line\n"));
	if (ft_strnstr(line, "NO ", size) && !game->key[NO])
		game->key[NO] = 1;
	else if (ft_strnstr(line, "NO ", size) && game->key[NO])
		return(printf("We need to exit here"));
	else if (ft_strnstr(line, "SO ", size) && !game->key[SO])
		game->key[SO] = 1;
	else if (ft_strnstr(line, "SO ", size) && game->key[NO])
		return(printf("We need to exit here"));
	else if (ft_strnstr(line, "EA ", size) && !game->key[EA])
		game->key[EA] = 1;
	else if (ft_strnstr(line, "EA ", size) && game->key[NO])
		return(printf("We need to exit here"));
	else if (ft_strnstr(line, "WE ", size) && !game->key[WE])
		game->key[WE] = 1;
	else if (ft_strnstr(line, "WE ", size) && game->key[NO])
		return(printf("We need to exit here"));
	else
		return(validate_line_aux(game, line, size));
}
