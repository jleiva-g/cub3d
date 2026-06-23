/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregueir <gregueir@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 13:02:28 by jleiva-g          #+#    #+#             */
/*   Updated: 2026/06/23 12:12:20 by gregueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	is_player(char cell)
{
	return (cell == 'N' || cell == 'S' || cell == 'E' || cell == 'O');
}

void	search_player(t_game *game, char *line, int y)
{
	int	i;

	while (line && line[i])
	{
		if (is_player(line[i]))
		{
			game->player.pos.x = (float)i + 0.5f;
			game->player.pos.y = (float)y + 0.5f;
			if (line[i] == 'N')
				game->player.dir.y = 1;
			else if (line[i] == 'S')
				game->player.dir.y = -1;
			else if (line[i] == 'E')
				game->player.dir.x = 1;
			else
				game->player.dir.x = -1;
		}
		i++;
	}
}

int	is_not_wall(char cell)
{
	return (cell == '0' || cell == 'N' || cell == 'S'
		|| cell == 'E' || cell == 'W' || cell == 'D');
}

int	is_valid_map(char cell)
{
	return (cell == '0' || cell == 'N' || cell == 'S'
		|| cell == 'E' || cell == 'W' || cell == 'D'
		|| cell == ' ' || cell == '1' || cell == '\n');
}
