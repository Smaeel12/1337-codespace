/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 09:54:33 by iboubkri          #+#    #+#             */
/*   Updated: 2025/02/13 10:22:57 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/main.h"

void	print_error(t_error error)
{
	if (error == EMPTY_FILE)
		ft_printf("Error\nEmpty File\n");
	if (error == NOT_RECT_MAP)
		ft_printf("Error\nMap should be rectangular\n");
	if (error == INVALID_EXT)
		ft_printf("Error\nFile should end with .ber extension\n");
	if (error == FILE_NOT_FOUND)
		ft_printf("Error\nFile couldn't be found\n");
	if (error == MAP_INVALID)
		ft_printf("Error\nMap is invalid\n");
	if (error == MLX_INS)
		ft_printf("Error\nCan't initialize mlx\n");
	if (error == TILES_ERR)
		ft_printf("Error\nCan't read tiles\n");
}
