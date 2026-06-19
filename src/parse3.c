/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregueir <gregueir@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 15:58:13 by gregueir          #+#    #+#             */
/*   Updated: 2026/06/19 12:53:03 by gregueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static	bool	is_border(t_game *game, int i, int j)
{
	if (i == 0 || j == 0 || i == game->map.height - 1
		|| j == game->map.width - 1)
		return (true);
	return (false);
}

static	bool	invalid_place(t_game *game, int i, int j)
{
	if (game->map.grid[i - 1][j] == ' ' || game->map.grid[i + 1][j] == ' '
		|| game->map.grid[i][j - 1] == ' ' || game->map.grid[i][j + 1] == ' ')
		return (true);
	return (false);
}

static	bool	validity_check(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map.grid[i])
	{
		j = 0;
		while (game->map.grid[i][j])
		{
			if (is_not_wall(game->map.grid[i][j]) && is_border(game, i, j))
				return (true);
			else if (is_not_wall(game->map.grid[i][j])
				&& invalid_place(game, i, j))
				return (true);
			j++;
		}
		i++;
	}
	return (false);
}

void	fill_line(t_game *game, int fill)
{
	int	i;

	i = 0;
	while (game->map.grid[fill][i] && game->map.grid[fill][i] != '\n')
		i++;
	while (i < game->map.width)
	{
		game->map.grid[fill][i] = ' ';
		i++;
	}
	game->map.grid[fill][i] = '\0';
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
	ft_strcpy(game->map.grid[i], line);
	if (ft_strlen(game->map.grid[i]) < (size_t)game->map.width)
		fill_line(game, i);
	if (i == (game->map.height - 1))
	{
		if (validity_check(game))
		{
			free(line);
			throw_error(game, ERR_Y);
		}
	}
}
