/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 03:28:16 by iboubkri          #+#    #+#             */
/*   Updated: 2025/03/05 03:39:32 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/main.h"


int animate_player(t_mlx *mlx)
{
	mlx->pc_anim.offset.x += mlx->pc_anim.direction.x * ACCELERATION;
	mlx->pc_anim.offset.y += mlx->pc_anim.direction.y * ACCELERATION;
	put_image(mlx, mlx->assets.space.frames[0], (mlx->map.stats.pc.x * SIZE), (mlx->map.stats.pc.y * SIZE));
	if (mlx->pc_anim.offset.x || mlx->pc_anim.offset.y)
		mlx->pc_anim.cur_frame = &mlx->pc_anim.walk[(2 & mlx->pc_anim.direction.x) | (3 & mlx->pc_anim.direction.y)];
	if (mlx->pc_anim.cur_frame->cframe >= mlx->pc_anim.cur_frame->tframes)
		mlx->pc_anim.cur_frame->cframe = 0;
	put_image(mlx,
		mlx->pc_anim.cur_frame->frames[mlx->pc_anim.cur_frame->cframe],
		(mlx->map.stats.pc.x * SIZE + mlx->pc_anim.offset.x),
		(mlx->map.stats.pc.y * SIZE + mlx->pc_anim.offset.y));
	mlx->pc_anim.cur_frame->cframe += 1;
	return 0;
}

int animate_enemy(t_mlx *mlx)
{
	int i;

	i = 0;
	if (mlx->assets.enemy.cframe >= mlx->assets.enemy.tframes)
		mlx->assets.enemy.cframe = 0;
	while (i < mlx->map.stats.nenemy)
	{
		if (mlx->map.stats.enemy_poss[i].x && mlx->map.stats.enemy_poss[i].y)
			put_image(mlx, mlx->assets.enemy.frames[mlx->assets.enemy.cframe],
				mlx->map.stats.enemy_poss[i].x * SIZE, mlx->map.stats.enemy_poss[i].y
				* SIZE);
		i++;
	}
	mlx->assets.enemy.cframe += 1;
	return 0;
}

int animate_clc(t_mlx *mlx)
{
	int i;

	i = 0;
	if (mlx->assets.clc.cframe >= 7)
		mlx->assets.clc.cframe = 0;
	while (i < mlx->map.stats.nclc)
	{
		if (mlx->map.stats.clc_poss[i].x && mlx->map.stats.clc_poss[i].y)
			put_image(mlx, mlx->assets.clc.frames[mlx->assets.clc.cframe],
				mlx->map.stats.clc_poss[i].x * SIZE, mlx->map.stats.clc_poss[i].y
				* SIZE);
		i++;
	}
	mlx->assets.clc.cframe += 1;
	return 0;

}

int reset_player_animation(t_mlx *mlx)
{
	mlx->num_mov += 1;
	ft_printf("number of movements: %i\n", mlx->num_mov);
	mlx->pc_anim.cur_frame = &mlx->pc_anim.idle[
		(2 & mlx->pc_anim.direction.x) | (3 & mlx->pc_anim.direction.y)];
	mlx->map.stats.pc.x += mlx->pc_anim.direction.x;
	mlx->map.stats.pc.y += mlx->pc_anim.direction.y;
	mlx->pc_anim.direction.x = 0;
	mlx->pc_anim.direction.y = 0;
	mlx->pc_anim.offset.x = 0;
	mlx->pc_anim.offset.y = 0;
	return 0;

}
