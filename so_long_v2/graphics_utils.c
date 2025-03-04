/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 19:34:12 by iboubkri          #+#    #+#             */
/*   Updated: 2025/03/01 12:10:32 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/main.h"

int	put_image(t_mlx *mlx, void *img, int x, int y)
{
	return (mlx_put_image_to_window(mlx->ptr, mlx->win, img, x, y));
}
