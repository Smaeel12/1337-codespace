/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resource_cleanup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:35:11 by iboubkri          #+#    #+#             */
/*   Updated: 2025/03/14 14:07:33 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/main.h"

static void	clear_assets(void *mlx_ptr, t_assets *assets)
{
	int	i;

	i = 0;
	while (assets->clc.frames && i < assets->clc.tframes)
		mlx_destroy_image(mlx_ptr, assets->clc.frames[i++]);
	free(assets->clc.frames);
	i = 0;
	while (assets->exit.frames && i < assets->exit.tframes)
		mlx_destroy_image(mlx_ptr, assets->exit.frames[i++]);
	free(assets->exit.frames);
	i = 0;
	while (assets->wall.frames && i < assets->wall.tframes)
		mlx_destroy_image(mlx_ptr, assets->wall.frames[i++]);
	free(assets->wall.frames);
	i = 0;
	while (assets->space.frames && i < assets->space.tframes)
		mlx_destroy_image(mlx_ptr, assets->space.frames[i++]);
	free(assets->space.frames);
	i = 0;
	while (assets->enemy.frames && i < assets->enemy.tframes)
		mlx_destroy_image(mlx_ptr, assets->enemy.frames[i++]);
	free(assets->enemy.frames);
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

int	clear_stats(t_stats *stats)
{
	free(stats->clc_poss);
	free(stats->enemy_poss);
	return (0);
}

int	clear_player(void *mlx_ptr, t_frames *anim)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < anim[i].tframes)
		{
			mlx_destroy_image(mlx_ptr, anim[i].frames[j]);
			j++;
		}
		free(anim[i].frames);
		i++;
	}
	return (0);
}

int	exit_program(t_mlx *mlx)
{
	int	i;

	if (mlx->map.stats.err)
		stats_errors(mlx->map.stats.err);
	if (mlx->err && (mlx->err != FAILED || mlx->err == SUCCESS))
		mlx_errors(mlx->err);
	if (mlx->map.err && (mlx->err != FAILED || mlx->err == SUCCESS))
		map_errors(mlx->map.err);
	ft_lstclear(&mlx->map.stats.clc_poss, free);
	ft_lstclear(&mlx->map.stats.enemy_poss, free);
	free2(mlx->map.grid);
	clear_stats(&mlx->map.stats);
	clear_assets(mlx->ptr, &mlx->assets);
	clear_player(mlx->ptr, mlx->pc_anim.idle);
	clear_player(mlx->ptr, mlx->pc_anim.walk);
	i = 0;
	while (mlx->pc_anim.death.frames && i < mlx->pc_anim.death.tframes)
		mlx_destroy_image(mlx->ptr, mlx->pc_anim.death.frames[i++]);
	free(mlx->pc_anim.death.frames);
	if (mlx->win)
		mlx_destroy_window(mlx->ptr, mlx->win);
	if (mlx->ptr)
		mlx_destroy_display(mlx->ptr);
	free(mlx->ptr);
	exit(0);
}
