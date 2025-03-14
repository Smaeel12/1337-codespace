/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 03:28:16 by iboubkri          #+#    #+#             */
/*   Updated: 2025/03/14 14:08:48 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/main.h"

int	init_additional_assets(t_mlx *mlx)
{
	mlx->assets.clc.tframes = 7;
	mlx->assets.exit.tframes = 2;
	mlx->assets.space.tframes = 1;
	mlx->assets.wall.tframes = 1;
	mlx->pc_anim.death.tframes = 17;
	split_sprite_to_frames(mlx->ptr, &mlx->assets.exit, "assets/exit.xpm");
	split_sprite_to_frames(mlx->ptr, &mlx->assets.space, "assets/space.xpm");
	split_sprite_to_frames(mlx->ptr, &mlx->assets.clc, "assets/clc.xpm");
	split_sprite_to_frames(mlx->ptr, &mlx->assets.wall, "assets/wall.xpm");
	split_sprite_to_frames(mlx->ptr, &mlx->pc_anim.death, "assets/death.xpm");
	if (!mlx->assets.exit.frames || !mlx->assets.space.frames
		|| !mlx->assets.clc.frames || !mlx->assets.wall.frames
		|| !mlx->pc_anim.death.frames)
		return (mlx->err = LOAD_ASSETS, exit_program(mlx));
	mlx->assets.enemy.tframes = 5;
	mlx->assets.enemy.cframe = 0;
	split_sprite_to_frames(mlx->ptr, &mlx->assets.enemy, "assets/enemy.xpm");
	if (!mlx->assets.enemy.frames)
		return (mlx->err = LOAD_ASSETS, exit_program(mlx));
	return (0);
}

int	init_player_idle_assets(t_mlx *mlx)
{
	mlx->pc_anim.idle[0].tframes = 2;
	mlx->pc_anim.idle[1].tframes = 2;
	mlx->pc_anim.idle[2].tframes = 2;
	mlx->pc_anim.idle[3].tframes = 2;
	split_sprite_to_frames(mlx->ptr, &mlx->pc_anim.idle[0],
		"assets/idle/right_idle.xpm");
	split_sprite_to_frames(mlx->ptr, &mlx->pc_anim.idle[2],
		"assets/idle/left_idle.xpm");
	split_sprite_to_frames(mlx->ptr, &mlx->pc_anim.idle[1],
		"assets/idle/down_idle.xpm");
	split_sprite_to_frames(mlx->ptr, &mlx->pc_anim.idle[3],
		"assets/idle/up_idle.xpm");
	if (!mlx->pc_anim.idle[0].frames || !mlx->pc_anim.idle[1].frames
		|| !mlx->pc_anim.idle[2].frames || !mlx->pc_anim.idle[3].frames)
		return (mlx->err = LOAD_ASSETS, exit_program(mlx));
	mlx->pc_anim.cur_frame = &mlx->pc_anim.idle[1];
	return (0);
}

int	init_player_walk_assets(t_mlx *mlx)
{
	mlx->pc_anim.walk[0].tframes = 4;
	mlx->pc_anim.walk[1].tframes = 4;
	mlx->pc_anim.walk[2].tframes = 4;
	mlx->pc_anim.walk[3].tframes = 4;
	split_sprite_to_frames(mlx->ptr, &mlx->pc_anim.walk[0],
		"assets/walk/left_walk.xpm");
	split_sprite_to_frames(mlx->ptr, &mlx->pc_anim.walk[2],
		"assets/walk/right_walk.xpm");
	split_sprite_to_frames(mlx->ptr, &mlx->pc_anim.walk[1],
		"assets/walk/down_walk.xpm");
	split_sprite_to_frames(mlx->ptr, &mlx->pc_anim.walk[3],
		"assets/walk/up_walk.xpm");
	if (!mlx->pc_anim.walk[0].frames || !mlx->pc_anim.walk[1].frames
		|| !mlx->pc_anim.walk[2].frames || !mlx->pc_anim.walk[3].frames)
		return (mlx->err = LOAD_ASSETS, exit_program(mlx));
	return (0);
}

int	init_assets(t_mlx *mlx)
{
	init_additional_assets(mlx);
	init_player_idle_assets(mlx);
	init_player_walk_assets(mlx);
	return (0);
}
