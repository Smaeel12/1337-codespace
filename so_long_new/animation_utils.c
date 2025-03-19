/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:12:02 by iboubkri          #+#    #+#             */
/*   Updated: 2025/03/19 00:21:32 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/main.h"

static int	copy_pixels(t_img *frame, t_img *img, int idx)
{
	char	*dst;
	char	*src;
	int		y;
	int		x;

	y = 0;
	while (y < SIZE)
	{
		x = 0;
		while (x < SIZE)
		{
			dst = frame->addr + (y * frame->sline + x * (frame->bpp / 8));
			src = img->addr + (y * img->sline + ((idx * SIZE + x) * (img->bpp
							/ 8)));
			*(unsigned int *)dst = *(unsigned int *)src;
			x++;
		}
		y++;
	}
	return (0);
}

int	split_sprite_to_frames(void *mlx_ptr, t_frames *stc, char *filename)
{
	t_img	frame;
	t_img	img;
	int		i;

	i = 0;
	img.ptr = mlx_xpm_file_to_image(mlx_ptr, filename, &img.size, &img.size);
	if (!img.ptr)
		return (stc->frames = NULL, 1);
	stc->frames = (void **)malloc((stc->tframes + 1) * sizeof(void *));
	if (!stc->frames)
		return (1);
	img.addr = mlx_get_data_addr(img.ptr, &img.bpp, &img.sline, &img.endian);
	while (i < stc->tframes)
	{
		frame.ptr = mlx_new_image(mlx_ptr, SIZE, SIZE);
		frame.addr = mlx_get_data_addr(frame.ptr, &frame.bpp, &frame.sline,
				&frame.endian);
		copy_pixels(&frame, &img, i);
		stc->frames[i] = frame.ptr;
		i++;
	}
	mlx_destroy_image(mlx_ptr, img.ptr);
	stc->frames[i] = NULL;
	return (0);
}

int	put_string_to_window(t_mlx *mlx)
{
	char	*str;

	put_image(mlx, mlx->assets.wall.frames[0], &(t_point){5, 0});
	mlx_string_put(mlx->ptr, mlx->win, 45, 20, 0xFFD700, "Number of Movement:");
	str = ft_itoa(mlx->nmoves);
	mlx_string_put(mlx->ptr, mlx->win, 175, 20, 0xFFD700, str);
	free(str);
	return (0);
}
