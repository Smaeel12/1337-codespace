/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_controls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:14:19 by iboubkri          #+#    #+#             */
/*   Updated: 2025/02/14 12:17:28 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/main.h"

int move_player(t_mlx *mlx, int px, int py)
{
	// if (((char *) (ft_get_node(mlx->map.map, (mlx->map.pp.y / mlx->tiles.tsize) + !!py)->content)) [(mlx->map.pp.y / mlx->tiles.tsize) + !!px])
	printf("[%i \\ %i] \n", (mlx->map.pp.y / mlx->tiles.tsize) + !!py, (mlx->map.pp.x / mlx->tiles.tsize) + !!px);
	
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->tiles.space, mlx->map.pp.x, mlx->map.pp.y);
	mlx->map.pp.x += px;
	mlx->map.pp.y += py;
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->tiles.player, mlx->map.pp.x, mlx->map.pp.y);
	return(0);
}