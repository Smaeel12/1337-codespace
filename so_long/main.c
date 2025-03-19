/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:01:02 by iboubkri          #+#    #+#             */
/*   Updated: 2025/03/19 01:08:33 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/main.h"

static int	init_program(t_mlx *mlx, char *map_file)
{
	t_point	scr;
	int		fd;

	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		return (mlx->err = COPEN_FILE, exit_program(mlx));
	load_map(mlx, fd);
	mlx->ptr = mlx_init();
	if (!mlx->ptr)
		return (mlx->err = MLX_FAILED, exit_program(mlx));
	mlx_get_screen_size(mlx->ptr, &scr.x, &scr.y);
	if (mlx->map.size.x * SIZE >= scr.x || mlx->map.size.y * SIZE >= scr.y)
		return (mlx->map.err = BIG_MAP, exit_program(mlx));
	init_assets(mlx);
	mlx->win = mlx_new_window(mlx->ptr, mlx->map.size.x * SIZE, mlx->map.size.y
			* SIZE, "GAME OF THRONES");
	if (!mlx->win)
		return (mlx->err = MLX_WIN, exit_program(mlx));
	render_map(mlx);
	mlx_hook(mlx->win, 17, 0, exit_program, mlx);
	mlx_hook(mlx->win, 2, 1L << 0, keypress, mlx);
	if (BONUS_MODE)
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
		mlx = (t_mlx){0, 0, {0, {0}, {0}, 0}, {{0}, {0}, {0}, {0}, {0}, {0},
		{0}, {0}}, 0, {0, {0}, {0}, 0}, 0, 0};
		ext = ft_strrchr(av[1], '.');
		if (!ext || ft_strlen(ext) != 4 || ft_strncmp(".ber", ext,
				ft_strlen(ext)) || ext == av[1] || (ft_strlen(av[1]) > 4
				&& *(ext - 1) == '/'))
			return (mlx_errors(INV_EXT));
		init_program(&mlx, av[1]);
	}
	return (0);
}
