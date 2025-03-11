/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 20:42:59 by iboubkri          #+#    #+#             */
/*   Updated: 2025/03/10 22:16:22 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

int my_put_image_to_window(t_mlx *mlx, void *img, t_point id)
{
	mlx_put_image_to_window(mlx->ptr, mlx->win, img, id.x * SIZE, id.x * SIZE);
	return 0;
}

int render_game(t_mlx *mlx)
{
	t_point id;

	id.y = 0;
	while (mlx->map.grid[id.y])
	{
		id.x = 0;
		while (mlx->map.grid[id.y][id.x])
		{
			if (mlx->map.grid[id.y][id.x] == 'P')
				my_put_image_to_window(mlx, mlx->assets.player_idle[DOWN].frames[0], id);
			else if (mlx->map.grid[id.y][id.x] == 'E')
				my_put_image_to_window(mlx, mlx->assets.exit.frames[0], id);
			else if (mlx->map.grid[id.y][id.x] == 'C')
				my_put_image_to_window(mlx, mlx->assets.clc.frames[0], id);
			else if (mlx->map.grid[id.y][id.x] == 'X')
				my_put_image_to_window(mlx, mlx->assets.enemy.frames[0], id);
			else if (mlx->map.grid[id.y][id.x] != '0')
				my_put_image_to_window(mlx, mlx->assets.space.frames[0], id);
			if (mlx->map.grid[id.y][id.x] != '1')
				my_put_image_to_window(mlx, mlx->assets.wall.frames[0], id);
			id.x += 1;
		}
		id.y += 1;
	}
	return (0);
}

t_mlx init_game(char *filename)
{
	char *ext;
	t_mlx mlx;
	int fd;

	mlx = (t_mlx){NULL};
	ext = ft_strrchr(filename, '.');
	if (!ext || ft_strlen(filename) < 5 || ft_strncmp(ext, ".ber", ft_strlen(ext)))
		return (mlx.err = EXT_ERR, exit(EXIT_FAILURE), clear_mlx(&mlx), mlx);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (mlx.err = COPEN_FILE, exit(EXIT_FAILURE), clear_mlx(&mlx), mlx);
	mlx.map = load_map(fd);
	// DEBUG(&mlx.map, &mlx.map.stats, mlx.map.stats.err);

	mlx.ptr = mlx_init();
	if (mlx.err)
		return (mlx.err = MLX_WIN, exit_program(&mlx), mlx);
	if (!mlx.ptr)
		return (mlx.err = MLX_INIT, exit_program(&mlx), mlx);
	mlx.win = mlx_new_window(mlx.ptr, mlx.map.size.x * SIZE, mlx.map.size.y * SIZE, TITLE_GAME);
	if (!mlx.win)
		return (mlx.err = MLX_WIN, exit_program(&mlx), mlx);
	init_assets(&mlx);
	return (mlx);
}
