/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:12:02 by iboubkri          #+#    #+#             */
/*   Updated: 2025/03/06 23:22:29 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/main.h"

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

int init_additional_assets(t_mlx *mlx)
{
	mlx->assets.clc.tframes = 7;
	mlx->assets.exit.tframes = 2;
	mlx->assets.space.tframes = 1;
	mlx->assets.wall.tframes = 1;

	split_sprite_to_frames(mlx->ptr, &mlx->assets.exit, "assets/exit.xpm");
	split_sprite_to_frames(mlx->ptr, &mlx->assets.space, "assets/space.xpm");
	split_sprite_to_frames(mlx->ptr, &mlx->assets.clc, "assets/clc.xpm");
	split_sprite_to_frames(mlx->ptr, &mlx->assets.wall, "assets/wall.xpm");
	if (!mlx->assets.exit.frames || !mlx->assets.space.frames || !mlx->assets.clc.frames || !mlx->assets.wall.frames)
		return (mlx->err = LOAD_ASSETS, exit_program(mlx));

	mlx->assets.enemy.tframes = 5;
	mlx->assets.enemy.cframe = 0;
	split_sprite_to_frames(mlx->ptr, &mlx->assets.enemy, "assets/enemy.xpm");
	if (!mlx->assets.enemy.frames)
		return (mlx->err = LOAD_ASSETS, exit_program(mlx));
	return 0;
}

int init_player_idle_assets(t_mlx *mlx)
{
	mlx->pc_anim.idle[0].tframes = 2;
	mlx->pc_anim.idle[1].tframes = 2;
	mlx->pc_anim.idle[2].tframes = 2;
	mlx->pc_anim.idle[3].tframes = 2;
	split_sprite_to_frames(mlx->ptr, &mlx->pc_anim.idle[0],
						   "assets/idle/right_idle.xpm");
	split_sprite_to_frames(mlx->ptr, &mlx->pc_anim.idle[2],
						   "assets/idle/left_idle.xpm");
	split_sprite_to_frames(mlx->ptr, &mlx->pc_anim.idle[1],
						   "assets/idle/down_idle.xpm");
	split_sprite_to_frames(mlx->ptr, &mlx->pc_anim.idle[3],
						   "assets/idle/up_idle.xpm");
	if (!mlx->pc_anim.idle[0].frames || !mlx->pc_anim.idle[1].frames || !mlx->pc_anim.idle[2].frames || !mlx->pc_anim.idle[3].frames)
		return (mlx->err = LOAD_ASSETS, exit_program(mlx));
	return 0;
}

int init_player_walk_assets(t_mlx *mlx)
{

	mlx->pc_anim.walk[0].tframes = 4;
	mlx->pc_anim.walk[1].tframes = 4;
	mlx->pc_anim.walk[2].tframes = 4;
	mlx->pc_anim.walk[3].tframes = 4;
	split_sprite_to_frames(mlx->ptr, &mlx->pc_anim.walk[0],
						   "assets/walk/left_walk.xpm");
	split_sprite_to_frames(mlx->ptr, &mlx->pc_anim.walk[2],
						   "assets/walk/right_walk.xpm");
	split_sprite_to_frames(mlx->ptr, &mlx->pc_anim.walk[1],
						   "assets/walk/down_walk.xpm");
	split_sprite_to_frames(mlx->ptr, &mlx->pc_anim.walk[3],
						   "assets/walk/up_walk.xpm");
	if (!mlx->pc_anim.walk[0].frames || !mlx->pc_anim.walk[1].frames || !mlx->pc_anim.walk[2].frames || !mlx->pc_anim.walk[3].frames)
		return (mlx->err = LOAD_ASSETS, exit_program(mlx));
	return 0;
}

int init_assets(t_mlx *mlx)
{
	init_additional_assets(mlx);
	init_player_idle_assets(mlx);
	init_player_walk_assets(mlx);
	return (0);
}
