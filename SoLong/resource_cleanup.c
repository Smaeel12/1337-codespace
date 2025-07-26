/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resource_cleanup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:35:11 by iboubkri          #+#    #+#             */
/*   Updated: 2025/03/19 01:09:48 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/main.h"

static int	clear_animation(t_mlx *mlx, t_frames *frames, int size)
{
	int	i;
	int	j;

	i = 0;
	while (frames[i].frames && i < size)
	{
		j = 0;
		while (frames[i].frames[j])
			mlx_destroy_image(mlx->ptr, frames[i].frames[j++]);
		free(frames[i++].frames);
	}
	return (1);
}

int	free2(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		free(arr[i++]);
	free(arr);
	return (0);
}

int	exit_program(t_mlx *mlx)
{
	if (mlx->map.err)
		map_errors(mlx->map.err);
	if (mlx->err)
		mlx_errors(mlx->err);
	free2(mlx->map.grid);
	ft_lstclear(&mlx->map.cords.clc, free);
	ft_lstclear(&mlx->map.cords.enemy, free);
	ft_lstclear(&mlx->map.cords.player, free);
	ft_lstclear(&mlx->map.cords.exit, free);
	clear_animation(mlx, mlx->assets.player_idle, 4);
	clear_animation(mlx, mlx->assets.player_walk, 4);
	clear_animation(mlx, mlx->assets.enemy_walk, 4);
	clear_animation(mlx, (t_frames[]){mlx->assets.clc, {0}}, 1);
	clear_animation(mlx, (t_frames[]){mlx->assets.exit, {0}}, 1);
	clear_animation(mlx, (t_frames[]){mlx->assets.wall, {0}}, 1);
	clear_animation(mlx, (t_frames[]){mlx->assets.death_scene, {0}}, 1);
	clear_animation(mlx, (t_frames[]){mlx->assets.space, {0}}, 1);
	if (mlx->win)
		mlx_destroy_window(mlx->ptr, mlx->win);
	if (mlx->ptr)
		mlx_destroy_display(mlx->ptr);
	free(mlx->ptr);
	exit(0);
}
