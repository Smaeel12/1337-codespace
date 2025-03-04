/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_renderer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:12:22 by iboubkri          #+#    #+#             */
/*   Updated: 2025/03/02 17:10:45 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/main.h"

int	render_map(t_mlx *mlx)
{
	int	x;
	int	y;

	y = 0;
	while (y < mlx->map.size.y)
	{
		x = 0;
		while (x < mlx->map.size.x)
		{
			if (mlx->map.arr[y][x] == '1')
				put_image(mlx, mlx->assets.wall.frames[0], x * SIZE, y * SIZE);
			if (mlx->map.arr[y][x] == 'E')
				put_image(mlx, mlx->assets.exit.frames[0], x * SIZE, y * SIZE);
			if (mlx->map.arr[y][x] == 'P')
			{
				put_image(mlx, mlx->pc_anim.idle[1].frames[0], x * SIZE, y * SIZE);
				mlx->pc_anim.cur_frame = &mlx->pc_anim.idle[1];
			}
			if (mlx->map.arr[y][x] == 'C')
				put_image(mlx, mlx->assets.clc.frames[0], x * SIZE, y * SIZE);
			if (mlx->map.arr[y][x] == '0')
				put_image(mlx, mlx->assets.space.frames[0], x * SIZE, y * SIZE);
			if (mlx->map.arr[y][x] == 'X')
				put_image(mlx, mlx->assets.enemy.frames[0], x * SIZE, y * SIZE);
			x++;
		}
		y++;
	}
	return (0);
}
