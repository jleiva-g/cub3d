/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleiva-g <jleiva-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 06:39:50 by jleiva-g          #+#    #+#             */
/*   Updated: 2026/06/26 13:45:27 by jleiva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d_bonus.h"

mlx_texture_t	*get_texture(t_game *game, t_ray ray)
{
	if (ray.is_door)
		return (game->tex.door);
	else if (ray.side == 0 && ray.ray_dir.x > 0)
		return (game->tex.east);
	else if (ray.side == 0)
		return (game->tex.west);
	else if (ray.ray_dir.y > 0)
		return (game->tex.south);
	else
		return (game->tex.north);
}

uint32_t	get_pixel(mlx_texture_t *tex, int x, int y)
{
	int	i;

	i = (y * tex->width + x) * 4;
	return (
		(tex->pixels[i] << 24)
		| (tex->pixels[i + 1] << 16)
		| (tex->pixels[i + 2] << 8)
		| tex->pixels[i + 3]
	);
}
