/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 09:54:33 by iboubkri          #+#    #+#             */
/*   Updated: 2025/02/13 13:14:43 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/main.h"

void	print_error(t_error error)
{
	ft_printf("\033[1;31mError\033[0m\n");
	if (error == EMPTY_FILE)
		ft_printf("Map file is empty. Please provide a valid map file.\n");
	if (error == NOT_RECT_MAP)
		ft_printf("Invalid map format: Map must be rectangular (all rows same \
length).\n");
	if (error == INVALID_EXT)
		ft_printf("Map file must have '.ber' extension.\n");
	if (error == FILE_NOT_FOUND)
		ft_printf("Map file not found. Check if the path is correct.\n");
	if (error == MAP_INVALID)
		ft_printf("No valid path exists between player, collectibles, \
and exit.\n");
	if (error == MLX_INS)
		ft_printf("Failed to initialize MLX. Check system requirements.\n");
	if (error == TILES_ERR)
		ft_printf("Failed to load texture files\n");
}
