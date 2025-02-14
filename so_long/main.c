/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:01:02 by iboubkri          #+#    #+#             */
/*   Updated: 2025/02/13 13:57:00 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/main.h"

void	init_mlx(t_mlx *mlx)
{
	mlx->ptr = NULL;
	mlx->win = NULL;
	mlx->map = (t_map){NULL, {0, 0}, {0, 0}};
	mlx->tiles = (t_tiles){NULL, NULL, NULL, NULL, NULL, 0};
	mlx->stats = (t_stats){0, 0};
	mlx->err = 0;
}

int	main(int ac, char **av)
{
	t_mlx	mlx;

	if (ac >= 2)
	{
		init_mlx(&mlx);
		if (check_map(&mlx, av[1]))
			kill_program(&mlx);
		run_game(&mlx);
	}
	else
	{
		ft_printf("Error\nInclude a map file .ber\n");
		return (1);
	}
	return (0);
}
