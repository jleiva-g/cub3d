/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleiva-g <jleiva-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 14:22:52 by jleiva-g          #+#    #+#             */
/*   Updated: 2026/05/27 13:14:40 by jleiva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	draw_square(mlx_image_t *img, int sx, int sy, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < MM_TILE)
	{
		x = 0;
		while (x < MM_TILE)
		{
			mlx_put_pixel(img,
				sx + x + WIDTH - MM_TILE * (MM_SIZE + 2),
				sy + y + HEIGHT - MM_TILE * (MM_SIZE + 2),
				color);
			x++;
		}
		y++;
	}
}

static void	draw_tile(t_game *game, int x, int y)
{
	t_point	mmap;
	int		color;

	mmap.x = (int) game->player.pos.x - (MM_SIZE / 2) + x;
	mmap.y = (int) game->player.pos.y - (MM_SIZE / 2) + y;
	color = 0x00000000;
	if (mmap.x >= 0 && mmap.y >= 0
		&& mmap.x < game->map.width
		&& mmap.y < game->map.height)
	{
		if (is_not_wall(game->map.grid[(int) mmap.y][(int) mmap.x]))
			color = 0x227722FF;
		else if (game->map.grid[(int) mmap.y][(int) mmap.x] == '1')
			color = 0x225522FF;
		if (game->map.grid[(int) mmap.y][(int) mmap.x] == 'D')
			color = 0x222277FF;
	}
	draw_square(game->img, x * MM_TILE, y * MM_TILE, color);
}

void	render_minimap(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < MM_SIZE)
	{
		x = 0;
		while (x < MM_SIZE)
		{
			draw_tile(game, x, y);
			x++;
		}
		y++;
	}
	x = (MM_SIZE / 2) * MM_TILE;
	draw_square(game->img, x, x, 0xCC2222FF);
}
