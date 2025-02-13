/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:35:11 by iboubkri          #+#    #+#             */
/*   Updated: 2025/02/13 10:04:58 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/main.h"

void	destroy_tiles(t_mlx *mlx)
{
	if (!mlx->ptr || !mlx->tiles.wall)
		return ;
	mlx_destroy_image(mlx->ptr, mlx->tiles.wall);
	mlx_destroy_image(mlx->ptr, mlx->tiles.exit);
	mlx_destroy_image(mlx->ptr, mlx->tiles.player);
	mlx_destroy_image(mlx->ptr, mlx->tiles.clc);
	mlx_destroy_image(mlx->ptr, mlx->tiles.space);
}

void	kill_program(t_mlx *mlx)
{
	if (mlx->err)
		print_error(mlx->err);
	ft_lstclear(&mlx->map.map, free);
	destroy_tiles(mlx);
	if (mlx->win)
		mlx_destroy_window(mlx->ptr, mlx->win);
	if (mlx->ptr)
		mlx_destroy_display(mlx->ptr);
	free(mlx->ptr);
	exit(0);
}
