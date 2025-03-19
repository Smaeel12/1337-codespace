/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_strings.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:07:27 by iboubkri          #+#    #+#             */
/*   Updated: 2025/03/19 00:58:16 by iboubkri         ###   ########.fr       */
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
	else if (error == INV_EDGES)
		ft_printf("Error\nMap must be surounded with walls\n", 30);
	else if (error == PATH_ERR)
		ft_printf("Error\nAll collectibles and exit must be reachable\n", 45);
	else if (error == PLAYER_ERR)
		ft_printf("Error\nThere must be exactly one player on the map\n", 47);
	else if (error == EXIT_ERR)
		ft_printf("Error\nThere must be exactly one exit on the map\n", 46);
	else if (error == COINS_ERR)
		ft_printf("Error\nThere must be one or more coins on the map\n", 46);
	else if (error == INV_STATS)
		ft_printf("Error\nMap must have exactly one player, one exit,\
 and at least one coin\n", 72);
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
