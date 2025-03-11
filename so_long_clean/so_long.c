/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 00:45:52 by iboubkri          #+#    #+#             */
/*   Updated: 2025/03/10 21:47:24 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

int main(int ac, char **av)
{
	t_mlx mlx;

	if (ac != 2)
		return write(2, NO_FILE_ERR, ft_strlen(NO_FILE_ERR)), 1;
	mlx = init_game(av[1]);
	render_game(&mlx);
	mlx_hook(mlx.win, 17, 0, exit_program, &mlx);
	// mlx_loop_hook(mlx.ptr, update_game, &mlx);
	mlx_loop(mlx.ptr);
	return 0;
}
