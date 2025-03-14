/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:01:02 by iboubkri          #+#    #+#             */
/*   Updated: 2025/03/14 20:12:33 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/main.h"

static int	keypress(int keycode, t_mlx *mlx)
{
	if (keycode == ESCAPE)
		return (mlx->err = OK, exit_program(mlx));
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
	usleep(0.070 * MICROSEC);
	if (mlx->err == FAILED)
	{
		if (mlx->pc_anim.death.cframe >= mlx->pc_anim.death.tframes)
			exit_program(mlx);
		put_image(mlx, mlx->pc_anim.death.frames[mlx->pc_anim.death.cframe],
			mlx->map.stats.player_pos.x * SIZE, mlx->map.stats.player_pos.y
			* SIZE);
		mlx->pc_anim.death.cframe += 1;
	}
	else if (mlx->err == SUCCESS)
		exit_program(mlx);
	else
	{
		animate_clc(mlx);
		animate_enemy(mlx);
		animate_player(mlx);
		if (abs(mlx->pc_anim.offset.x) >= SIZE
			|| abs(mlx->pc_anim.offset.y) >= SIZE)
			reset_player_animation(mlx);
	}
	return (0);
}

static int	init_program(t_mlx *mlx, char *map_file)
{
	int	fd;

	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		return (mlx->err = COPEN_FILE, exit_program(mlx));
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
	mlx_hook(mlx->win, 2, 1L << 0, keypress, mlx);
	mlx_loop_hook(mlx->ptr, render_frames, mlx);
	mlx_loop(mlx->ptr);
	return (0);
}

int	main(int ac, char **av)
{
	char	*ext;
	t_mlx	mlx;

	if (ac > 2 || ac < 2)
		return (ft_printf("Error\nInsufficient number of arguments. Please\
 provide only a map file.\n"), 1);
	else
	{
		mlx = (t_mlx){NULL, NULL, {NULL, {NULL, NULL, {0}, {0}, 0}, {0}, 0},
		{{0}, {0}, {0}, {0}, {0}}, {NULL, {0}, {0}, {0}, {0}, {0}}, 0, 0};
		ext = ft_strrchr(av[1], '.');
		if (!ext || ft_strncmp(".ber", ext, ft_strlen(ext))
			|| (ft_strlen(av[1]) > 3 && *(ext - 1) == '/'))
			return (mlx_errors(INV_EXT));
		init_program(&mlx, av[1]);
	}
	return (0);
}
