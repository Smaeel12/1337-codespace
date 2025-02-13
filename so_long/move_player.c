/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:14:19 by iboubkri          #+#    #+#             */
/*   Updated: 2025/02/13 09:34:55 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/main.h"

int	move_player(t_mlx *mlx, int x, int y)
{
	char	*new_pos;

	new_pos = ft_get_node(mlx->map.map, mlx->map.pp.y + y)->content
		+ mlx->map.pp.x + x;
	if (*new_pos == '1')
		return (0);
	if (*new_pos == 'C')
	{
		mlx->stats.nclc -= 1;
		*new_pos = 'T';
	}
	if (*new_pos == 'E')
	{
		if (!mlx->stats.nclc)
			kill_program(mlx);
		else
			return (0);
	}
	put_image(mlx, mlx->tiles.space, mlx->map.pp.x, mlx->map.pp.y);
	mlx->map.pp.x += x;
	mlx->map.pp.y += y;
	put_image(mlx, mlx->tiles.player, mlx->map.pp.x, mlx->map.pp.y);
	return (0);
}
