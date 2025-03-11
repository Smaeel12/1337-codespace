/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:12:02 by iboubkri          #+#    #+#             */
/*   Updated: 2025/03/10 21:56:08 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

static int copy_pixels(t_img *frame, t_img *img, int idx)
{
	char *dst;
	char *src;
	int y;
	int x;

	y = 0;
	while (y < SIZE)
	{
		x = 0;
		while (x < SIZE)
		{
			dst = frame->addr + (y * frame->sline + x * (frame->bpp / 8));
			src = img->addr + (y * img->sline + ((idx * SIZE + x) * (img->bpp / 8)));
			*(unsigned int *)dst = *(unsigned int *)src;
			x++;
		}
		y++;
	}
	return (0);
}

static int split_sprite_to_frames(void *mlx_ptr, t_frames *stc, char *filename)
{
	t_img frame;
	t_img img;
	int i;

	i = 0;
	stc->frames = (void **)malloc((stc->tframes + 1) * sizeof(void *));
	if (!stc->frames)
		return (1);
	img.ptr = mlx_xpm_file_to_image(mlx_ptr, filename, &img.size, &img.size);
	if (!img.ptr)
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

static int init_additional_assets(t_mlx *mlx)
{
	mlx->assets.clc.tframes = 7;
	mlx->assets.exit.tframes = 2;
	mlx->assets.space.tframes = 1;
	mlx->assets.wall.tframes = 1;

	split_sprite_to_frames(mlx->ptr, &mlx->assets.space, "assets/space.xpm");
	split_sprite_to_frames(mlx->ptr, &mlx->assets.clc, "assets/clc.xpm");
	split_sprite_to_frames(mlx->ptr, &mlx->assets.wall, "assets/wall.xpm");
	if (!mlx->assets.exit.frames || !mlx->assets.space.frames || !mlx->assets.clc.frames || !mlx->assets.wall.frames)
		return (mlx->err = LOAD_ASSETS, 1);

	mlx->assets.enemy.tframes = 5;
	mlx->assets.enemy.cframe = 0;
	split_sprite_to_frames(mlx->ptr, &mlx->assets.enemy, "assets/enemy.xpm");
	if (!mlx->assets.enemy.frames)
		return (mlx->err = LOAD_ASSETS, 1);
	return 0;
}

static int init_player_idle_assets(t_mlx *mlx)
{
	mlx->assets.player_idle[LEFT].cframe = 0;
	mlx->assets.player_idle[RIGHT].cframe = 0;
	mlx->assets.player_idle[UP].cframe = 0;
	mlx->assets.player_idle[DOWN].cframe = 0;

	mlx->assets.player_idle[LEFT].tframes = 2;
	mlx->assets.player_idle[RIGHT].tframes = 2;
	mlx->assets.player_idle[UP].tframes = 2;
	mlx->assets.player_idle[DOWN].tframes = 2;

	split_sprite_to_frames(mlx->ptr, &mlx->assets.player_idle[LEFT],
						   "assets/idle/right_idle.xpm");
	split_sprite_to_frames(mlx->ptr, &mlx->assets.player_idle[RIGHT],
						   "assets/idle/right_idle.xpm");
	split_sprite_to_frames(mlx->ptr, &mlx->assets.player_idle[UP],
						   "assets/idle/right_idle.xpm");
	split_sprite_to_frames(mlx->ptr, &mlx->assets.player_idle[DOWN],
						   "assets/idle/right_idle.xpm");
	if (!mlx->assets.player_idle[LEFT].frames || !mlx->assets.player_idle[RIGHT].frames || !mlx->assets.player_idle[UP].frames || !mlx->assets.player_idle[DOWN].frames)
		return (mlx->err = LOAD_ASSETS, 1);
	return 0;
}

static int init_player_walk_assets(t_mlx *mlx)
{
	mlx->assets.player_walk[LEFT].cframe = 0;
	mlx->assets.player_walk[RIGHT].cframe = 0;
	mlx->assets.player_walk[UP].cframe = 0;
	mlx->assets.player_walk[DOWN].cframe = 0;

	mlx->assets.player_walk[LEFT].tframes = 2;
	mlx->assets.player_walk[RIGHT].tframes = 2;
	mlx->assets.player_walk[UP].tframes = 2;
	mlx->assets.player_walk[DOWN].tframes = 2;

	split_sprite_to_frames(mlx->ptr, &mlx->assets.player_walk[LEFT],
						   "assets/idle/right_idle.xpm");
	split_sprite_to_frames(mlx->ptr, &mlx->assets.player_walk[RIGHT],
						   "assets/idle/right_idle.xpm");
	split_sprite_to_frames(mlx->ptr, &mlx->assets.player_walk[UP],
						   "assets/idle/right_idle.xpm");
	split_sprite_to_frames(mlx->ptr, &mlx->assets.player_walk[DOWN],
						   "assets/idle/right_idle.xpm");
	if (!mlx->assets.player_walk[LEFT].frames || !mlx->assets.player_walk[RIGHT].frames || !mlx->assets.player_walk[UP].frames || !mlx->assets.player_walk[DOWN].frames)
		return (mlx->err = LOAD_ASSETS, 1);
	return 0;
}

int init_assets(t_mlx *mlx)
{
	init_additional_assets(mlx);
	init_player_idle_assets(mlx);
	init_player_walk_assets(mlx);
	return (0);
}
