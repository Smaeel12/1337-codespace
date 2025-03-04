/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:12:02 by iboubkri          #+#    #+#             */
/*   Updated: 2025/02/25 20:01:23 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/main.h"

void copy_pixel(t_img *frame, t_img *img, int idx)
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
			dst = frame->addr + (y *frame->sline + x * (frame->bpp / 8));
			src = img->addr + (y * img->sline + ((idx * SIZE + x) * (img->bpp / 8)));
			*(unsigned int *)dst = *(unsigned int *)src;
			x++;
		}
		y++;
	}
}

void **split_sprite_to_frames(void *mlx_ptr, int tframes, char *filename)
{
	void	**frames_arr;
	t_img	frame;
	t_img	img;
	int		i;

	i = 0;
	frames_arr = (void **)malloc((tframes  + 1)* sizeof(void *));
	if (!frames_arr)
		return NULL;
	img.ptr = mlx_xpm_file_to_image(mlx_ptr, filename, &img.size, &img.size);
	if (!img.ptr)
		return NULL;
	img.addr = mlx_get_data_addr(img.ptr, &img.bpp, &img.sline, &img.endian);
	while (i < tframes)
	{
		frame.ptr = mlx_new_image(mlx_ptr, SIZE, SIZE);
		frame.addr = mlx_get_data_addr(frame.ptr, &frame.bpp, &frame.sline, &frame.endian);
		copy_pixel(&frame, &img, i);
		frames_arr[i] = frame.ptr;
		i++;
	}
	mlx_destroy_image(mlx_ptr, img.ptr);
	frames_arr[i] = NULL;
	return frames_arr;
}
