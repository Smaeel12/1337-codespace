/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:04:28 by iboubkri          #+#    #+#             */
/*   Updated: 2025/03/14 13:56:02 by iboubkri         ###   ########.fr       */
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

int	scan_map(t_stats *stats, char **grid, t_point size, t_point id)
{
	id.y = 0;
	while (grid && grid[id.y] && !stats->err)
	{
		id.x = 0;
		while (grid[id.y][id.x] && !stats->err)
		{
			stats->err = ((id.x == 0 || id.y == 0 || id.x == size.x - 1
						|| id.y == size.y - 1) && grid[id.y][id.x] != '1')
				* INV_EDGES;
			if (grid[id.y][id.x] == 'P' && !stats->player_pos.x)
				stats->player_pos = id;
			else if (grid[id.y][id.x] == 'E' && !stats->exit_pos.x)
				stats->exit_pos = id;
			else if (grid[id.y][id.x] == 'C')
				ft_lstadd_back(&stats->clc_poss, ft_lstnew(new_cords(id)));
			else if (grid[id.y][id.x] == 'X')
				ft_lstadd_back(&stats->enemy_poss, ft_lstnew(new_cords(id)));
			else if (grid[id.y][id.x] != '0' && grid[id.y][id.x] != '1')
				stats->err = INV_CHAR | ((grid[id.y][id.x] == 'P'
							|| grid[id.y][id.x] == 'E') * INV_STATS);
			id.x += 1;
		}
		id.y += 1;
	}
	return (stats->err);
}
