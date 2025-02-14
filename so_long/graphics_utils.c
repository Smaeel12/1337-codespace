/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 19:34:12 by iboubkri          #+#    #+#             */
/*   Updated: 2025/02/14 12:05:24 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/main.h"

void	put_image(t_mlx *mlx, void *img, int x, int y)
{
	mlx_put_image_to_window(mlx->ptr, mlx->win, img, x * mlx->tiles.tsize, y * mlx->tiles.tsize);
}
