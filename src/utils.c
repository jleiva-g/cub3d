/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregueir <gregueir@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 13:02:28 by jleiva-g          #+#    #+#             */
/*   Updated: 2026/06/19 12:53:45 by gregueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	is_player(char cell)
{
	return (cell == 'N' || cell == 'S' || cell == 'E' || cell == 'O');
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
