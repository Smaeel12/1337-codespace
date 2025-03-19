/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 03:28:16 by iboubkri          #+#    #+#             */
/*   Updated: 2025/03/19 01:09:05 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/main.h"

static int	animate_clc(t_mlx *mlx, t_list *lst)
{
	t_list	*temp;
	t_point	*point;

	temp = lst;
	while (temp)
	{
		point = (t_point *)temp->content;
		put_image(mlx, mlx->assets.clc.frames[mlx->fps
			% mlx->assets.clc.tframes], point);
		temp = temp->next;
	}
	return (0);
}

static int	animate_player(t_mlx *mlx, t_point *point)
{
	mlx->player.offset.x += mlx->player.direction.x * ACCELERATION;
	mlx->player.offset.y += mlx->player.direction.y * ACCELERATION;
	put_image(mlx, mlx->assets.space.frames[0], point);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->player.cur_frame->frames[
		mlx->fps % mlx->player.cur_frame->tframes],
		point->x * SIZE + mlx->player.offset.x,
		point->y * SIZE + mlx->player.offset.y);
	return (0);
}

static int	animate_enemy(t_mlx *mlx, t_list *lst)
{
	t_point	*ps;
	t_point	new;

	new = (t_point){(rand() % 3) - 1, (rand() % 3) - 1};
	while (lst)
	{
		ps = ((t_point *)lst->content);
		put_image(mlx, mlx->assets.space.frames[0], ps);
		if (mlx->map.grid[ps->y + new.y][ps->x + new.x] == 'P' && !(new.x
				&&new.y))
			mlx->err = EXIT_SIG;
		if (mlx->map.grid[ps->y + new.y][ps->x + new.x] == '0' && !(mlx->fps
				% 3) && !(new.x && new.y))
		{
			mlx->map.grid[ps->y][ps->x] = '0';
			*ps = (t_point){ps->x + new.x, ps->y + new.y};
			mlx->map.grid[ps->y][ps->x] = 'X';
		}
		put_image(mlx,
			mlx->assets.enemy_walk[(3 & new.x) | (2 & new.y)].frames[mlx->fps
			% mlx->assets.enemy_walk->tframes], ps);
		lst = lst->next;
	}
	return (0);
}

static int	death_scene(t_mlx *mlx, t_point *point)
{
	if (mlx->fps
		% mlx->assets.death_scene.tframes >= mlx->assets.death_scene.tframes
		- 1)
		exit_program(mlx);
	put_image(mlx, mlx->assets.death_scene.frames[mlx->fps
		% mlx->assets.death_scene.tframes], point);
	return (0);
}

int	render_frames(t_mlx *mlx)
{
	put_string_to_window(mlx);
	if (mlx->err != EXIT_SIG)
	{
		animate_player(mlx, mlx->map.cords.player->content);
		animate_clc(mlx, mlx->map.cords.clc);
		animate_enemy(mlx, mlx->map.cords.enemy);
		if (abs(mlx->player.offset.x) >= SIZE
			|| abs(mlx->player.offset.y) >= SIZE)
		{
			mlx->player.cur_frame = &mlx->assets.player_idle[mlx->player.side];
			((t_point *)mlx->map.cords.player->content)->x
				+= mlx->player.direction.x;
			((t_point *)mlx->map.cords.player->content)->y
				+= mlx->player.direction.y;
			mlx->player.direction.x = 0;
			mlx->player.direction.y = 0;
			mlx->player.offset.x = 0;
			mlx->player.offset.y = 0;
		}
	}
	else
		death_scene(mlx, mlx->map.cords.player->content);
	mlx->fps += 1;
	usleep(0.1 * MICROSEC);
	return (0);
}
