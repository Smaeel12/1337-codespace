/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:12:22 by iboubkri          #+#    #+#             */
/*   Updated: 2025/02/13 10:50:03 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/main.h"

void	render_map(t_mlx *mlx)
{
	char	*line;
	int		x;
	int		y;

	y = 0;
	while (y < mlx->map.msize.y)
	{
		line = ft_get_node(mlx->map.map, y)->content;
		x = 0;
		while (x < mlx->map.msize.x)
		{
			if (line[x] == '1')
				put_image(mlx, mlx->tiles.wall, x, y);
			if (line[x] == 'E')
				put_image(mlx, mlx->tiles.exit, x, y);
			if (line[x] == 'P')
				put_image(mlx, mlx->tiles.player, x, y);
			if (line[x] == 'C')
				put_image(mlx, mlx->tiles.clc, x, y);
			if (line[x] == '0')
				put_image(mlx, mlx->tiles.space, x, y);
			x++;
		}
		y++;
	}
}
