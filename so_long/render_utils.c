/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 03:28:16 by iboubkri          #+#    #+#             */
/*   Updated: 2025/03/14 20:14:58 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/main.h"

int	animate_player(t_mlx *mlx)
{
	mlx->pc_anim.offset.x += mlx->pc_anim.direction.x * ACCELERATION;
	mlx->pc_anim.offset.y += mlx->pc_anim.direction.y * ACCELERATION;
	put_image(mlx, mlx->assets.space.frames[0], (mlx->map.stats.player_pos.x
			* SIZE), (mlx->map.stats.player_pos.y * SIZE));
	if (mlx->pc_anim.offset.x || mlx->pc_anim.offset.y)
		mlx->pc_anim.cur_frame = &mlx->pc_anim.walk[
			(2 & mlx->pc_anim.direction.x) | (3 & mlx->pc_anim.direction.y)];
	if (mlx->pc_anim.cur_frame->cframe >= mlx->pc_anim.cur_frame->tframes)
		mlx->pc_anim.cur_frame->cframe = 0;
	put_image(mlx,
		mlx->pc_anim.cur_frame->frames[mlx->pc_anim.cur_frame->cframe],
		(mlx->map.stats.player_pos.x * SIZE + mlx->pc_anim.offset.x),
		(mlx->map.stats.player_pos.y * SIZE + mlx->pc_anim.offset.y));
	mlx->pc_anim.cur_frame->cframe += 1;
	return (0);
}

int	animate_enemy(t_mlx *mlx)
{
	t_list	*temp;

	temp = mlx->map.stats.enemy_poss;
	if (mlx->assets.enemy.cframe >= mlx->assets.enemy.tframes)
		mlx->assets.enemy.cframe = 0;
	while (temp)
	{
		put_image(mlx, mlx->assets.enemy.frames[mlx->assets.enemy.cframe],
			((t_point *)temp->content)->x * SIZE, ((t_point *)temp->content)->y
			* SIZE);
		temp = temp->next;
	}
	mlx->assets.enemy.cframe += 1;
	return (0);
}

int	animate_clc(t_mlx *mlx)
{
	t_list	*temp;

	temp = mlx->map.stats.clc_poss;
	if (mlx->assets.clc.cframe >= mlx->assets.clc.tframes)
		mlx->assets.clc.cframe = 0;
	while (temp)
	{
		put_image(mlx, mlx->assets.clc.frames[mlx->assets.clc.cframe],
			((t_point *)temp->content)->x * SIZE, ((t_point *)temp->content)->y
			* SIZE);
		temp = temp->next;
	}
	mlx->assets.clc.cframe += 1;
	return (0);
}

int	reset_player_animation(t_mlx *mlx)
{
	mlx->num_mov += 1;
	ft_printf("number of movements: %i\n", mlx->num_mov);
	mlx->pc_anim.cur_frame = &mlx->pc_anim.idle[(2 & mlx->pc_anim.direction.x)
		| (3 & mlx->pc_anim.direction.y)];
	mlx->map.stats.player_pos.x += mlx->pc_anim.direction.x;
	mlx->map.stats.player_pos.y += mlx->pc_anim.direction.y;
	mlx->pc_anim.direction.x = 0;
	mlx->pc_anim.direction.y = 0;
	mlx->pc_anim.offset.x = 0;
	mlx->pc_anim.offset.y = 0;
	return (0);
}
