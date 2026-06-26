/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleiva-g <jleiva-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 11:19:57 by gregueir          #+#    #+#             */
/*   Updated: 2026/06/26 13:45:17 by jleiva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d_bonus.h"

void	clean_path(t_game *game)
{
	char	*tmp;
	char	*current;

	current = game->tex.north_path;
	tmp = ft_strnstr(current, "\n", ft_strlen(current));
	if (tmp)
		*tmp = '\0';
	current = game->tex.south_path;
	tmp = ft_strnstr(current, "\n", ft_strlen(current));
	if (tmp)
		*tmp = '\0';
	current = game->tex.east_path;
	tmp = ft_strnstr(current, "\n", ft_strlen(current));
	if (tmp)
		*tmp = '\0';
	current = game->tex.west_path;
	tmp = ft_strnstr(current, "\n", ft_strlen(current));
	if (tmp)
		*tmp = '\0';
}

char	*extract_path(char *line)
{
	char	**str;
	char	*out;

	str = ft_split(line, ' ');
	if (!ft_strnstr(str[1], ".png", ft_strlen(str[1])))
	{
		free_split(str);
		return (NULL);
	}
	out = ft_strdup(str[1]);
	free_split(str);
	return (out);
}

static	int	combine_to_hex(int r, int g, int b)
{
	return (r << 24 | g << 16 | b << 8 | 0xFF);
}

static	bool	check_values(char *r, char *g, char *b, int n[3])
{
	n[0] = ft_atoi(r);
	n[1] = ft_atoi(g);
	n[2] = ft_atoi(b);
	if (n[0] >= 0 && n[0] <= 255
		&& n[1] >= 0 && n[1] <= 255
		&& n[2] >= 0 && n[2] <= 255)
		return (true);
	else
		return (false);
}

int	extract_color(char *line)
{
	char	**str;
	char	**num;
	int		out;
	int		n[3];

	str = ft_split(line, ' ');
	if (!ft_strnstr(str[1], ",", ft_strlen(str[1])))
	{
		free_split(str);
		return (-1);
	}
	num = ft_split(str[1], ',');
	if (!num[2])
		return (free_split(str), free_split(num), -1);
	if (check_values(num[0], num[1], num[2], n))
		out = combine_to_hex(n[0], n[1], n[2]);
	else
		out = -1;
	free_split(str);
	free_split(num);
	return (out);
}
