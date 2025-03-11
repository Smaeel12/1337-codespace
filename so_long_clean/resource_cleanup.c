/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resource_cleanup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:35:11 by iboubkri          #+#    #+#             */
/*   Updated: 2025/03/10 22:16:10 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

static void clear_player_assests(void *mlx_ptr, t_frames *frames)
{
	int i;
	int j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (frames[i].frames && frames[i].frames[j])
			mlx_destroy_image(mlx_ptr, frames[i].frames[j++]);
		free(frames[i].frames);
		i++;
	}
}

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
	clear_player_assests(mlx_ptr, assets->player_idle);
	clear_player_assests(mlx_ptr, assets->player_walk);
}

int clear_grid(char **grid)
{
	int i;

	i = 0;
	while (grid[i])
	{
		free(grid[i]);
		i++;
	}
	free(grid);
	return 0;
}

int clear_map(t_map *map)
{
	if (map->stats.err)
		map_errors(map->stats.err);
	if (map->err)
		map_errors(map->err);
	ft_lstclear(&map->stats.clc_poss, free);
	ft_lstclear(&map->stats.enm_poss, free);
	ft_lstclear(&map->stats.exit_pos, free);
	ft_lstclear(&map->stats.player_pos, free);
	clear_grid(map->grid);
	return (0);
}

int clear_mlx(t_mlx *mlx)
{
	if (mlx->err)
		mlx_errors(mlx->err);
	if (mlx->win)
		mlx_destroy_window(mlx->ptr, mlx->win);
	if (mlx->ptr)
		mlx_destroy_display(mlx->ptr);
	free(mlx->ptr);
	return 0;
}

int mlx_errors(int error)
{
	write(2, ERROR_MSG, ft_strlen(ERROR_MSG));
	if (error == EXT_ERR)
		write(2, "\tInvalid file extension. Map file must end with '.ber'\n", 55);
	else if (error == COPEN_FILE)
		write(2, "\tCannot open map file. Check if file exists and permissions\n", 60);
	else if (error == MLX_INIT)
		write(2, "\tFailed to initialize MLX\n", 26);
	else if (error == LOAD_ASSETS)
		write(2, "\tFailed to load game assets\n", 28);
	else if (error == MLX_WIN)
		write(2, "\tFailed to create window\n", 25);
	return 0;
}

int map_errors(t_error error)
{
	write(2, ERROR_MSG, ft_strlen(ERROR_MSG));
	if (error == EMPTY_FILE)
		write(2, "\tMap file is empty\n", 19);
	else if (error == NOT_RECT_MAP)
		write(2, "\tMap must be rectangular\n", 25);
	else if (error == INV_CHAR)
		write(2, "\tInvalid character in map\n", 26);
	else if (error == INV_EDGES)
		write(2, "\tMap must be surrounded by walls\n", 33);
	else if (error == INV_STATS)
		write(2, "\tMap must contain 1 player, 1 exit and at least 1 collectible\n", 62);
	else if (error == INV_REACH)
		write(2, "\tAll collectibles and exit must be reachable\n", 45);
	return (0);
}

int exit_program(t_mlx *mlx)
{
	clear_map(&mlx->map);
	clear_assets(&mlx->ptr, &mlx->assets);
	clear_mlx(mlx);
	exit(EXIT_FAILURE);
}

// int clear_stats(t_stats *stats)
// {
// 	free(stats->clc_poss);
// 	free(stats->enemy_poss);
// 	return (0);
// }

// int clear_player(void *mlx_ptr, t_frames *anim)
// {
// 	int i;
// 	int j;

// 	i = 0;
// 	while (i < 4)
// 	{
// 		j = 0;
// 		while (j < anim[i].tframes)
// 		{
// 			mlx_destroy_image(mlx_ptr, anim[i].frames[j]);
// 			j++;
// 		}
// 		free(anim[i].frames);
// 		i++;
// 	}
// 	return (0);
// }

// int exit_program(t_mlx *mlx)
// {
// 	if (mlx->err)
// 		mlx_errors(mlx->err);
// 	if (mlx->map.err)
// 		map_errors(mlx->map.err);
// 	free_array(mlx->map.arr);
// 	clear_stats(&mlx->map.stats);
// 	clear_assets(mlx->ptr, &mlx->assets);
// 	clear_player(mlx->ptr, mlx->pc_anim.idle);
// 	clear_player(mlx->ptr, mlx->pc_anim.walk);
// 	if (mlx->win)
// 		mlx_destroy_window(mlx->ptr, mlx->win);
// 	if (mlx->ptr)
// 		mlx_destroy_display(mlx->ptr);
// 	free(mlx->ptr);
// 	exit(0);
// }
