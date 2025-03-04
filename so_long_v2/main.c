/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:01:02 by iboubkri          #+#    #+#             */
/*   Updated: 2025/03/02 21:27:55 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/main.h"

static int	keypress(int keycode, t_mlx *mlx)
{
	if (keycode == ESCAPE)
		return (mlx->err = EXT_OK, exit_program(mlx));
	if (keycode == RIGHT)
		return (move_player(mlx, 1, 0));
	if (keycode == LEFT)
		return (move_player(mlx, -1, 0));
	if (keycode == UP)
		return (move_player(mlx, 0, -1));
	if (keycode == DOWN)
		return (move_player(mlx, 0, 1));
	return (0);
}

static int	render_frames(t_mlx *mlx)
{
	int	i;

	i = 0;
	if (mlx->assets.clc.cframe >= 7)
		mlx->assets.clc.cframe = 0;
	if (mlx->assets.enemy.cframe >= mlx->assets.enemy.tframes)
		mlx->assets.enemy.cframe = 0;
	while (i < mlx->map.stats.nclc)
	{
		if (mlx->map.stats.clc_poss[i].x && mlx->map.stats.clc_poss[i].y)
			put_image(mlx, mlx->assets.clc.frames[mlx->assets.clc.cframe],
				mlx->map.stats.clc_poss[i].x * SIZE, mlx->map.stats.clc_poss[i].y
				* SIZE);
		i++;
	}
	if (mlx->pc_anim.cur_frame->cframe >= mlx->pc_anim.cur_frame->tframes)
		mlx->pc_anim.cur_frame->cframe = 0;
	mlx->pc_anim.offset.x += mlx->pc_anim.direction.x * ACCELERATION;
	mlx->pc_anim.offset.y += mlx->pc_anim.direction.y * ACCELERATION;
	if (mlx->pc_anim.offset.x || mlx->pc_anim.offset.y)
		mlx->pc_anim.cur_frame = &mlx->pc_anim.walk[
			(2 & mlx->pc_anim.direction.x) | (3 & mlx->pc_anim.direction.y)];
	put_image(mlx, mlx->assets.space.frames[0], (mlx->map.stats.pc.x * SIZE),
		(mlx->map.stats.pc.y * SIZE));
	put_image(mlx,
		mlx->pc_anim.cur_frame->frames[mlx->pc_anim.cur_frame->cframe],
		(mlx->map.stats.pc.x * SIZE + mlx->pc_anim.offset.x),
		(mlx->map.stats.pc.y * SIZE + mlx->pc_anim.offset.y));
	i = 0;
	while (i < mlx->map.stats.nenemy)
	{
		if (mlx->map.stats.enemy_poss[i].x && mlx->map.stats.enemy_poss[i].y)
			put_image(mlx, mlx->assets.enemy.frames[mlx->assets.enemy.cframe],
				mlx->map.stats.enemy_poss[i].x * SIZE, mlx->map.stats.enemy_poss[i].y
				* SIZE);
		i++;
	}
	usleep(0.1337 * MICROSEC);
	if (abs(mlx->pc_anim.offset.x) >= SIZE
		|| abs(mlx->pc_anim.offset.y) >= SIZE)
	{
		mlx->num_mov += 1;
		ft_printf("number of movements: %i\n", mlx->num_mov);
		mlx->pc_anim.cur_frame = &mlx->pc_anim.idle[
			(2 & mlx->pc_anim.direction.x) | (3 & mlx->pc_anim.direction.y)];
		mlx->map.stats.pc.x += mlx->pc_anim.direction.x;
		mlx->map.stats.pc.y += mlx->pc_anim.direction.y;
		mlx->pc_anim.direction.x = 0;
		mlx->pc_anim.direction.y = 0;
		mlx->pc_anim.offset.x = 0;
		mlx->pc_anim.offset.y = 0;
	}
	mlx->pc_anim.cur_frame->cframe += 1;
	mlx->assets.clc.cframe += 1;
	mlx->assets.enemy.cframe += 1;
	return (0);
}

static int	init_program(t_mlx *mlx, char *map_file)
{
	int	fd;

	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		return (mlx->map.err = COPEN_FILE, exit_program(mlx));
	load_map(mlx, fd);
	mlx->ptr = mlx_init();
	if (!mlx->ptr)
		return (mlx->err = MLX_FAILED, exit_program(mlx));
	init_assets(mlx);
	mlx->win = mlx_new_window(mlx->ptr, mlx->map.size.x * SIZE, mlx->map.size.y
			* SIZE, "GAME OF THRONES");
	if (!mlx->win)
		return (mlx->err = MLX_WIN, exit_program(mlx));
	render_map(mlx);
	mlx_hook(mlx->win, 17, 0, exit_program, mlx);
	mlx_key_hook(mlx->win, keypress, mlx);
	mlx_loop_hook(mlx->ptr, render_frames, mlx);
	mlx_loop(mlx->ptr);
	return (0);
}

int	main(int ac, char **av)
{
	char	*ext;
	t_mlx	mlx;

	if (ac >= 2)
	{
		mlx = (t_mlx){NULL};
		ext = ft_strrchr(av[1], '.');
		if (!ext || (ft_strncmp(ext, ".ber", ft_strlen(ext))
				&& ft_strlen(ext) > 3))
			return (map_errors(INV_EXT));
		init_program(&mlx, av[1]);
	}
	else
	{
		ft_printf("Error\nInclude a map file .ber\n");
		return (1);
	}
	return (0);
}
