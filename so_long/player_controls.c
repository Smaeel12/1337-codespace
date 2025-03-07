/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_controls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:14:19 by iboubkri          #+#    #+#             */
/*   Updated: 2025/03/05 03:50:27 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/main.h"

int	move_player(t_mlx *mlx, int x, int y)
{
	int		i;
	char	*c;

	c = &mlx->map.arr[mlx->map.stats.pc.y + y][mlx->map.stats.pc.x + x];
	printf("%i || %i\n", mlx->pc_anim.offset.y, mlx->pc_anim.offset.x);
	if (mlx->pc_anim.offset.x || mlx->pc_anim.offset.y)
		return 0;
	if (*c == '1' || (*c == 'E' && mlx->map.stats.eaten < mlx->map.stats.nclc))
		return (0);
	else if (*c == 'C')
	{
		i = 0;
		while (i < mlx->map.stats.nclc)
		{
			if (mlx->map.stats.clc_poss[i].x == mlx->map.stats.pc.x + x
				&& mlx->map.stats.clc_poss[i].y == mlx->map.stats.pc.y + y)
				mlx->map.stats.clc_poss[i] = (t_point) {0};
			i++;
		}
		*c = '0';
		mlx->map.stats.eaten += 1;
		if (mlx->map.stats.eaten >= mlx->map.stats.nclc)
			put_image(mlx, mlx->assets.exit.frames[1], mlx->map.stats.exit_pos.x
				* SIZE, mlx->map.stats.exit_pos.y * SIZE);
		put_image(mlx, mlx->assets.space.frames[0], (mlx->map.stats.pc.x + x)
			* SIZE, (mlx->map.stats.pc.y + y) * SIZE);
	}
	else if ((*c == 'E' && mlx->map.stats.eaten >= mlx->map.stats.nclc) || *c == 'X')
		mlx->err = EXT_SIGNAL;
	mlx->pc_anim.direction.x = x;
	mlx->pc_anim.direction.y = y;
	return (0);
}
