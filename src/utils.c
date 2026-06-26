/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleiva-g <jleiva-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 13:02:28 by jleiva-g          #+#    #+#             */
/*   Updated: 2026/06/26 13:58:54 by jleiva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	is_player(char cell)
{
	return (cell == 'N' || cell == 'S' || cell == 'E' || cell == 'W');
}

void	update_player_info(t_game *game, char c, int x, int y)
{
	game->player.pos.x = (float)x + 0.5f;
	game->player.pos.y = (float)y + 0.5f;
	if (c == 'N')
		game->player.dir.y = 1;
	else if (c == 'S')
		game->player.dir.y = -1;
	else if (c == 'E')
		game->player.dir.x = 1;
	else
		game->player.dir.x = -1;
	game->player.plane.x = -game->player.dir.y * FOV;
	game->player.plane.y = game->player.dir.x * FOV;
}

void	search_player(t_game *game, char *line, int y)
{
	int			i;
	static int	doors = 0;

	i = 0;
	while (line && line[i])
	{
		if (is_player(line[i]))
			update_player_info(game, line[i], i, y);
		else if (line[i] == 'D')
		{
			game->doors[doors].x = i;
			game->doors[doors].y = y;
			doors++;
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
		|| cell == 'E' || cell == 'W'
		|| cell == ' ' || cell == '1' || cell == '\n');
}
