/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_renderer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:12:22 by iboubkri          #+#    #+#             */
/*   Updated: 2025/03/18 23:53:22 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/main.h"

int	render_map(t_mlx *mlx)
{
	t_point	idx;

	idx.y = 0;
	while (idx.y < mlx->map.size.y)
	{
		idx.x = 0;
		while (idx.x < mlx->map.size.x)
		{
			if (mlx->map.grid[idx.y][idx.x] == '1')
				put_image(mlx, mlx->assets.wall.frames[0], &idx);
			if (mlx->map.grid[idx.y][idx.x] == 'E')
				put_image(mlx, mlx->assets.exit.frames[0], &idx);
			if (mlx->map.grid[idx.y][idx.x] == 'P')
				put_image(mlx, mlx->assets.player_idle[DOWN].frames[0], &idx);
			if (mlx->map.grid[idx.y][idx.x] == 'C')
				put_image(mlx, mlx->assets.clc.frames[0], &idx);
			if (mlx->map.grid[idx.y][idx.x] == '0')
				put_image(mlx, mlx->assets.space.frames[0], &idx);
			if (mlx->map.grid[idx.y][idx.x] == 'X')
				put_image(mlx, mlx->assets.enemy_walk[DOWN].frames[0], &idx);
			idx.x++;
		}
		idx.y++;
	}
	return (0);
}
