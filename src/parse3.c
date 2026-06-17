/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregueir <gregueir@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 15:58:13 by gregueir          #+#    #+#             */
/*   Updated: 2026/06/17 18:15:10 by gregueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static	bool	is_border(t_game *game, int i, int j)
{
	if (i == 0 || j == 0 || i == game->map.height - 1 || j == game->map.width - 1)
		return (true);
	return (false);
}

// static	bool	validity_check(t_game *game)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (game->map.grid[i])
// 	{
// 		j = 0;
// 		while (game->map.grid[i][j])
// 		{
// 			if (is_border(game, i, j))
// 			j++;
// 		}
// 		i++;
// 	}
// }

void	load_map(t_game *game, char *line)
{
	int	size;
	int	i;

	size = ft_strlen(line);
	if ((size <= 1 || is_empty(line, size)) && game->map.check_map == 0)
		return ;
	else
		game->map.check_map++;
	i = game->map.check_map - 1;
	game->map.grid[i] = ft_strcpy(game->map.grid[i], line);
	if (i == (game->map.height - 1))
	{
		// if (validity_check(game))
		// {
		// 	free(line);
		// 	throw_error(game, ERR_Y);
		// }
	}
}
