/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregueir <gregueir@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 12:35:36 by gregueir          #+#    #+#             */
/*   Updated: 2026/06/03 13:09:02 by gregueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static	int	validate_line_aux(char *line, int size, int key[6])
{
	if (ft_strnstr(line, "F ", size) && !key[F])
		key[F] = 1;
	else if (ft_strnstr(line, "F ", size) && key[F])
		return(printf("We need to exit here 5"), -1);
	else if (ft_strnstr(line, "C ", size) && !key[C])
		key[C] = 1;
	else if (ft_strnstr(line, "C ", size) && key[C])
		return(printf("We need to exit here 6"), -1);
	else
		return(printf("Invalid line, we stop here\n"), -1);
	return (0);
}

int	is_empty(char *line, int size)
{
	int	i;

	i = 0;
	while(line[i] && i < size)
	{
		if (line[i] == ' ' || line[i] == '\n')
			i++;
		else
			return (0);
	}
	return (1);
}

int	validate_line(char *line, int key[6])
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

static	int	is_map(char *line)
{
	int	i;

	i = 0;
	while(line && line[i])
	{
		if (!is_valid_map(line[i]))
			return(printf("Invalid character in map"),EXIT_FAILURE);
		i++;
	}
	return (0);
}

int	validate_map(t_game *game, char *line)
{
	int	size;

	size = ft_strlen(line);
	if ((size <= 1 || is_empty(line, size)) && game->map.check_map == 0)
		return (0);
	else if ((size <= 1 || is_empty(line, size)) && game->map.check_map == 1)
		return (printf("Empty line in map, invalid"), EXIT_FAILURE);
	if (game->map.width < size)
		game->map.width = size;
	if (is_map(line))
		return(printf("\n"), EXIT_FAILURE);
	else
		game->map.check_map = 1;
	return (0);
}