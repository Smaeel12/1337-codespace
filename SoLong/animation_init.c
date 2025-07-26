/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 03:28:16 by iboubkri          #+#    #+#             */
/*   Updated: 2025/03/18 22:02:51 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/main.h"

int	init_additional_assets(t_mlx *mlx)
{
	mlx->assets.clc.tframes = 7;
	mlx->assets.exit.tframes = 2;
	mlx->assets.space.tframes = 1;
	mlx->assets.wall.tframes = 1;
	mlx->assets.death_scene.tframes = 17;
	split_sprite_to_frames(mlx->ptr, &mlx->assets.exit, "assets/exit.xpm");
	split_sprite_to_frames(mlx->ptr, &mlx->assets.space, "assets/space.xpm");
	split_sprite_to_frames(mlx->ptr, &mlx->assets.clc, "assets/clc.xpm");
	split_sprite_to_frames(mlx->ptr, &mlx->assets.wall, "assets/wall.xpm");
	split_sprite_to_frames(mlx->ptr, &mlx->assets.death_scene,
		"assets/death.xpm");
	if (!mlx->assets.exit.frames || !mlx->assets.space.frames
		|| !mlx->assets.clc.frames || !mlx->assets.wall.frames
		|| !mlx->assets.death_scene.frames)
		return (mlx->err = LOAD_ASSETS, exit_program(mlx));
	return (0);
}

int	init_enemy_walk_assets(t_mlx *mlx)
{
	mlx->assets.enemy_walk[RIGHT].tframes = 2;
	mlx->assets.enemy_walk[DOWN].tframes = 2;
	mlx->assets.enemy_walk[LEFT].tframes = 2;
	mlx->assets.enemy_walk[UP].tframes = 2;
	split_sprite_to_frames(mlx->ptr, &mlx->assets.enemy_walk[RIGHT],
		"assets/enemy/right_walk.xpm");
	split_sprite_to_frames(mlx->ptr, &mlx->assets.enemy_walk[DOWN],
		"assets/enemy/down_walk.xpm");
	split_sprite_to_frames(mlx->ptr, &mlx->assets.enemy_walk[LEFT],
		"assets/enemy/left_walk.xpm");
	split_sprite_to_frames(mlx->ptr, &mlx->assets.enemy_walk[UP],
		"assets/enemy/up_walk.xpm");
	if (!mlx->assets.enemy_walk[DOWN].frames
		|| !mlx->assets.enemy_walk[LEFT].frames
		|| !mlx->assets.enemy_walk[RIGHT].frames
		|| !mlx->assets.enemy_walk[UP].frames)
		return (mlx->err = LOAD_ASSETS, exit_program(mlx));
	return (0);
}

int	init_player_walk_assets(t_mlx *mlx)
{
	mlx->assets.player_walk[RIGHT].tframes = 4;
	mlx->assets.player_walk[DOWN].tframes = 4;
	mlx->assets.player_walk[LEFT].tframes = 4;
	mlx->assets.player_walk[UP].tframes = 4;
	split_sprite_to_frames(mlx->ptr, &mlx->assets.player_walk[RIGHT],
		"assets/walk/right_walk.xpm");
	split_sprite_to_frames(mlx->ptr, &mlx->assets.player_walk[DOWN],
		"assets/walk/down_walk.xpm");
	split_sprite_to_frames(mlx->ptr, &mlx->assets.player_walk[LEFT],
		"assets/walk/left_walk.xpm");
	split_sprite_to_frames(mlx->ptr, &mlx->assets.player_walk[UP],
		"assets/walk/up_walk.xpm");
	if (!mlx->assets.player_walk[DOWN].frames
		|| !mlx->assets.player_walk[LEFT].frames
		|| !mlx->assets.player_walk[RIGHT].frames
		|| !mlx->assets.player_walk[UP].frames)
		return (mlx->err = LOAD_ASSETS, exit_program(mlx));
	return (0);
}

int	init_player_idle_assets(t_mlx *mlx)
{
	mlx->assets.player_idle[RIGHT].tframes = 2;
	mlx->assets.player_idle[DOWN].tframes = 2;
	mlx->assets.player_idle[LEFT].tframes = 2;
	mlx->assets.player_idle[UP].tframes = 2;
	split_sprite_to_frames(mlx->ptr, &mlx->assets.player_idle[RIGHT],
		"assets/idle/right_idle.xpm");
	split_sprite_to_frames(mlx->ptr, &mlx->assets.player_idle[DOWN],
		"assets/idle/down_idle.xpm");
	split_sprite_to_frames(mlx->ptr, &mlx->assets.player_idle[LEFT],
		"assets/idle/left_idle.xpm");
	split_sprite_to_frames(mlx->ptr, &mlx->assets.player_idle[UP],
		"assets/idle/up_idle.xpm");
	if (!mlx->assets.player_idle[DOWN].frames
		|| !mlx->assets.player_idle[LEFT].frames
		|| !mlx->assets.player_idle[RIGHT].frames
		|| !mlx->assets.player_idle[UP].frames)
		return (mlx->err = LOAD_ASSETS, exit_program(mlx));
	return (0);
}

int	init_assets(t_mlx *mlx)
{
	init_player_idle_assets(mlx);
	init_player_walk_assets(mlx);
	init_enemy_walk_assets(mlx);
	init_additional_assets(mlx);
	mlx->player.cur_frame = &mlx->assets.player_idle[DOWN];
	return (0);
}
