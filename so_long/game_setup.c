/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:38:05 by iboubkri          #+#    #+#             */
/*   Updated: 2025/02/14 12:06:33 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/main.h"

int	read_tiles(t_mlx *mlx)
{
	if (!mlx->ptr)
		return (1);
	mlx->tiles.wall = mlx_xpm_file_to_image(mlx->ptr, "tiles/wall.xpm",
			&mlx->tiles.tsize, &mlx->tiles.tsize);
	mlx->tiles.exit = mlx_xpm_file_to_image(mlx->ptr, "tiles/exit.xpm",
			&mlx->tiles.tsize, &mlx->tiles.tsize);
	mlx->tiles.player = mlx_xpm_file_to_image(mlx->ptr, "tiles/player.xpm",
			&mlx->tiles.tsize, &mlx->tiles.tsize);
	mlx->tiles.clc = mlx_xpm_file_to_image(mlx->ptr, "tiles/clc.xpm",
			&mlx->tiles.tsize, &mlx->tiles.tsize);
	mlx->tiles.space = mlx_xpm_file_to_image(mlx->ptr, "tiles/space.xpm",
			&mlx->tiles.tsize, &mlx->tiles.tsize);
	if (!mlx->tiles.wall || !mlx->tiles.exit || !mlx->tiles.clc
		|| !mlx->tiles.player || !mlx->tiles.space)
		return (1);
	return (0);
}

int	keypress(int keycode, t_mlx *mlx)
{
	if (keycode == 'w')
		move_player(mlx, 0, -5);
	else if (keycode == 's')
		move_player(mlx, 0, 5);
	if (keycode == 'a')
		move_player(mlx, -5, 0);
	if (keycode == 'd')
		move_player(mlx, 5, 0);
	if (keycode == ESCAPE)
		kill_program(mlx);
	return (1);
}

int	run_game(t_mlx *mlx)
{
	mlx->ptr = mlx_init();
	if (!mlx->ptr)
		mlx->err = MLX_INS;
	if (read_tiles(mlx))
		mlx->err = TILES_ERR;
	if (mlx->err)
		kill_program(mlx);
	mlx->win = mlx_new_window(mlx->ptr, mlx->map.msize.x * mlx->tiles.tsize, mlx->map.msize.y * mlx->tiles.tsize, "GAME OF THRONES");
	render_map(mlx);
	mlx->map.pp.x *= mlx->tiles.tsize;
	mlx->map.pp.y *= mlx->tiles.tsize;
	mlx_hook(mlx->win, 2, 1L<<0, keypress, mlx);
	mlx_loop(mlx->ptr);
	return (1);
}
