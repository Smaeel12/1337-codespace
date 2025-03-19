/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:04:28 by iboubkri          #+#    #+#             */
/*   Updated: 2025/03/18 23:10:43 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/main.h"

int	search_path(char **grid, t_point start, t_point size, t_point *stats)
{
	if (start.x < 0 || start.x >= size.x || start.y < 0 || start.y >= size.y)
		return (0);
	if (grid[start.y][start.x] == 'E')
	{
		stats->x += 1;
		grid[start.y][start.x] = 'F';
	}
	if (grid[start.y][start.x] == '1' || grid[start.y][start.x] == 'F'
		|| grid[start.y][start.x] == 'X')
		return (0);
	stats->y += grid[start.y][start.x] == 'C';
	grid[start.y][start.x] = 'F';
	search_path(grid, (t_point){start.x + 1, start.y}, size, stats);
	search_path(grid, (t_point){start.x - 1, start.y}, size, stats);
	search_path(grid, (t_point){start.x, start.y + 1}, size, stats);
	search_path(grid, (t_point){start.x, start.y - 1}, size, stats);
	return (0);
}

static t_point	*new_cords(t_point cords)
{
	t_point	*new;

	new = (t_point *)malloc(sizeof(t_point));
	new->x = cords.x;
	new->y = cords.y;
	return (new);
}

int	check_wall(char **grid, t_point id, t_point size)
{
	return (((id.x == 0 || id.y == 0 || id.x == size.x - 1 || id.y == size.y
				- 1) && grid[id.y][id.x] != '1') * INV_EDGES);
}

int	scan_map(t_cords *stats, char **grid, t_point size)
{
	t_point	id;

	id.y = 0;
	while (grid && grid[id.y] && !stats->error)
	{
		id.x = 0;
		while (grid[id.y][id.x] && !stats->error)
		{
			stats->error = check_wall(grid, id, size);
			if (grid[id.y][id.x] == 'P')
				ft_lstadd_back(&stats->player, ft_lstnew(new_cords(id)));
			else if (grid[id.y][id.x] == 'E')
				ft_lstadd_back(&stats->exit, ft_lstnew(new_cords(id)));
			else if (grid[id.y][id.x] == 'C')
				ft_lstadd_back(&stats->clc, ft_lstnew(new_cords(id)));
			else if (grid[id.y][id.x] == 'X' && BONUS_MODE)
				ft_lstadd_back(&stats->enemy, ft_lstnew(new_cords(id)));
			else if (grid[id.y][id.x] != '0' && grid[id.y][id.x] != '1')
				stats->error = INV_CHAR;
			id.x += 1;
		}
		id.y += 1;
	}
	return (stats->error);
}
