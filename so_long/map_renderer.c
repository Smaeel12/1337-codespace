/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_renderer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:12:22 by iboubkri          #+#    #+#             */
/*   Updated: 2025/03/14 14:05:49 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/main.h"

int	put_image2(t_mlx *mlx, t_img *img, t_point idx)
{
	put_image(mlx, img, idx.x * SIZE, idx.y * SIZE);
	return (0);
}

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
				put_image2(mlx, mlx->assets.wall.frames[0], idx);
			if (mlx->map.grid[idx.y][idx.x] == 'E')
				put_image2(mlx, mlx->assets.exit.frames[0], idx);
			if (mlx->map.grid[idx.y][idx.x] == 'P')
				put_image2(mlx, mlx->pc_anim.idle[1].frames[0], idx);
			if (mlx->map.grid[idx.y][idx.x] == 'C')
				put_image2(mlx, mlx->assets.clc.frames[0], idx);
			if (mlx->map.grid[idx.y][idx.x] == '0')
				put_image2(mlx, mlx->assets.space.frames[0], idx);
			if (mlx->map.grid[idx.y][idx.x] == 'X')
				put_image2(mlx, mlx->assets.enemy.frames[0], idx);
			idx.x++;
		}
		idx.y++;
	}
	return (0);
}
