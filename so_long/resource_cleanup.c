/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resource_cleanup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:35:11 by iboubkri          #+#    #+#             */
/*   Updated: 2025/03/07 00:24:17 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/main.h"

static void clear_assets(void *mlx_ptr, t_assets *assets)
{
	int i;

	i = 0;
	while (i < assets->clc.tframes)
		mlx_destroy_image(mlx_ptr, assets->clc.frames[i++]);
	free(assets->clc.frames);
	i = 0;
	while (i < assets->exit.tframes)
		mlx_destroy_image(mlx_ptr, assets->exit.frames[i++]);
	free(assets->exit.frames);
	i = 0;
	while (i < assets->wall.tframes)
		mlx_destroy_image(mlx_ptr, assets->wall.frames[i++]);
	free(assets->wall.frames);
	i = 0;
	while (i < assets->space.tframes)
		mlx_destroy_image(mlx_ptr, assets->space.frames[i++]);
	free(assets->space.frames);
	i = 0;
	while (i < assets->enemy.tframes)
		mlx_destroy_image(mlx_ptr, assets->enemy.frames[i++]);
	free(assets->enemy.frames);
}

int map_errors(t_error error)
{
	write(2, "\033[31mError\n\033[0m", 15);
	if (error == EMPTY_FILE)
		write(2, "Map file is empty\n", 19);
	else if (error == NOT_RECT_MAP)
		write(2, "Map must be rectangular\n", 25);
	else if (error == INV_CHAR)
		write(2, "Invalid character in map\n", 26);
	else if (error == INV_EDGES)
		write(2, "Map must be surrounded by walls\n", 33);
	else if (error == DOUBLE_PLAYER)
		write(2, "Only one player position allowed\n", 34);
	else if (error == INV_STATS)
		write(2, "Map must contain 1 player, 1 exit and at least 1 collectible\n", 62);
	else if (error == INV_REACH)
		write(2, "All collectibles and exit must be reachable\n", 45);
	return (0);
}

int mlx_errors(t_error error)
{
	write(2, "\033[31mError\n\033[0m", 15);
	if (error == INV_EXT)
		write(2, "Invalid file extension. Map file must end with '.ber'\n", 55);
	else if (error == COPEN_FILE)
		write(2, "Cannot open map file. Check if file exists and permissions\n", 60);
	else if (error == MLX_FAILED)
		write(2, "Failed to initialize MLX\n", 26);
	else if (error == LOAD_ASSETS)
		write(2, "Failed to load game assets\n", 28);
	else if (error == MLX_WIN)
		write(2, "Failed to create window\n", 25);
	return (0);
}

int free_array(char **arr)
{
	int i;

	i = 0;
	while (arr && arr[i])
		free(arr[i++]);
	free(arr);
	return (0);
}

int clear_stats(t_stats *stats)
{
	free(stats->clc_poss);
	free(stats->enemy_poss);
	return (0);
}

int clear_player(void *mlx_ptr, t_frames *anim)
{
	int i;
	int j;

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

int exit_program(t_mlx *mlx)
{
	if (mlx->err)
		mlx_errors(mlx->err);
	if (mlx->map.err)
		map_errors(mlx->map.err);
	free_array(mlx->map.arr);
	clear_stats(&mlx->map.stats);
	clear_assets(mlx->ptr, &mlx->assets);
	clear_player(mlx->ptr, mlx->pc_anim.idle);
	clear_player(mlx->ptr, mlx->pc_anim.walk);
	if (mlx->win)
		mlx_destroy_window(mlx->ptr, mlx->win);
	if (mlx->ptr)
		mlx_destroy_display(mlx->ptr);
	free(mlx->ptr);
	exit(0);
}
