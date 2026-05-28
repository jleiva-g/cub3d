/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregueir <gregueir@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 12:35:36 by gregueir          #+#    #+#             */
/*   Updated: 2026/05/27 15:44:24 by gregueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	validate_line(char *line)
{
	int	size;

	size = ft_strlen(line);
	if (ft_strnstr(line, "NO ", size) ||
		ft_strnstr(line, "SO ", size) ||
		ft_strnstr(line, "WE ", size) ||
		ft_strnstr(line, "EA ", size) ||
		ft_strnstr(line, "F ", size) ||
		ft_strnstr(line, "C ", size))
		{
			printf("Found it\n");
			return (0);
		}
	else
		return(printf("Failed\n"));
	return (1);
}
