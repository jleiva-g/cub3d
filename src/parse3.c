/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregueir <gregueir@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 15:58:13 by gregueir          #+#    #+#             */
/*   Updated: 2026/06/17 17:48:15 by gregueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static	bool	validity_check(t_game *game)
{
	int	i;
	int	j;

	
}

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
	// if (i == (game->map.height - 1))
	// 	floodfill();
	//ft_printf("Height is %d and we're at %d\n", game->map.height, i);
	//ft_printf("%s", game->map.grid[i]);
}
