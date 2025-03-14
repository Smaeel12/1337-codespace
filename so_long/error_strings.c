/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_strings.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:07:27 by iboubkri          #+#    #+#             */
/*   Updated: 2025/03/14 14:07:58 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/main.h"

int	map_errors(t_error error)
{
	if (error == EMPTY_FILE)
		ft_printf("Error\nMap file is empty\n", 19);
	else if (error == NOT_RECT_MAP)
		ft_printf("Error\nMap must be rectangular\n", 25);
	else if (error == INV_CHAR)
		ft_printf("Error\nInvalid character in map\n", 26);
	else if (error == INV_STATS)
		ft_printf("Error\nMap must contain 1 player, 1 exit and at least 1\
 collectible\n", 62);
	else if (error == INV_REACH)
		ft_printf("Error\nAll collectibles and exit must be reachable\n", 45);
	return (0);
}

int	mlx_errors(t_error error)
{
	if (error == INV_EXT)
		ft_printf("Error\nInvalid file extension. Map file must end with\
 '.ber'\n", 55);
	else if (error == COPEN_FILE)
		ft_printf("Error\nCannot open map file. Check if file exists and\
 permissions\n", 60);
	else if (error == MLX_FAILED)
		ft_printf("Error\nFailed to initialize MLX\n", 26);
	else if (error == LOAD_ASSETS)
		ft_printf("Error\nFailed to load game assets\n", 28);
	else if (error == MLX_WIN)
		ft_printf("Error\nFailed to create window\n", 25);
	return (0);
}

int	stats_errors(t_error error)
{
	if (error == INV_CHAR)
		ft_printf("Error\nInvalid character on map\n", 32);
	else if (error == INV_STATS)
		ft_printf("Error\nMap must contain 1 player, 1 exit and at least 1\
 collectible\n", 62);
	else if (error == INV_EDGES)
		ft_printf("Error\nMap must be surrounded by walls\n", 33);
	return (0);
}
