/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:01:02 by iboubkri          #+#    #+#             */
/*   Updated: 2025/03/05 03:29:25 by iboubkri         ###   ########.fr       */
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
	usleep(0.1337 * MICROSEC);
	animate_clc(mlx);
	animate_enemy(mlx);
	animate_player(mlx);
	if (abs(mlx->pc_anim.offset.x) >= SIZE || abs(mlx->pc_anim.offset.y) >= SIZE)
	{
		reset_player_animation(mlx);
		if (mlx->err == EXT_SIGNAL)
			exit_program(mlx);
	}
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
