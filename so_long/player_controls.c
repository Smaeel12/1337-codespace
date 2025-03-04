/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_controls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:14:19 by iboubkri          #+#    #+#             */
/*   Updated: 2025/02/24 18:51:31 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/main.h"

int	move_player(t_mlx *mlx, int x, int y)
{
	char	*new_pos;

	new_pos = ft_get_node(mlx->map.map, mlx->map.pp.y + y)->content;
	new_pos += mlx->map.pp.x + x;

	if (*new_pos == '1' || (*new_pos == 'E' && mlx->stats.nclc))
		return 0;
	if (*new_pos == 'E' && !mlx->stats.nclc)
		kill_program(mlx);
	else if (*new_pos == 'C')
		return *new_pos = '0', mlx->stats.nclc -= 1, 0;
	mlx->map.pp.x += x;
	mlx->map.pp.y += y;
	return 0;
}