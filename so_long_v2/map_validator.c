/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:04:28 by iboubkri          #+#    #+#             */
/*   Updated: 2025/03/02 17:56:01 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/main.h"

static t_point	*new_cordinates(t_point cords)
{
	t_point	*new;

	new = (t_point *)malloc(sizeof(t_point));
	new->x = cords.x;
	new->y = cords.y;
	return (new);
}

static int	add_new_cords_to_queue(t_list **queue, t_point *point)
{
	ft_lstadd_back(queue, ft_lstnew(new_cordinates((t_point){point->x + 1,
				point->y})));
	ft_lstadd_back(queue, ft_lstnew(new_cordinates((t_point){point->x - 1,
				point->y})));
	ft_lstadd_back(queue, ft_lstnew(new_cordinates((t_point){point->x, point->y
				+ 1})));
	ft_lstadd_back(queue, ft_lstnew(new_cordinates((t_point){point->x, point->y
				- 1})));
	return (0);
}

int	search_path(t_map *map, t_point start, char edge)
{
	t_list	*queue;
	t_list	*head;
	t_point	*point;

	queue = NULL;
	ft_lstadd_back(&queue, ft_lstnew(new_cordinates(start)));
	while (queue)
	{
		head = queue;
		point = head->content;
		map->stats.next += map->arr[point->y][point->x] == 'E';
		if (!(point->x < 0 || point->x >= map->size.x || point->y < 0
				|| point->y >= map->size.y
				|| map->arr[point->y][point->x] == edge
				|| map->arr[point->y][point->x] == 'F'
				|| map->arr[point->y][point->x] == 'E'
				|| map->arr[point->y][point->x] == 'X'))
		{
			map->stats.nclc += map->arr[point->y][point->x] == 'C';
			map->arr[point->y][point->x] = 'F';
			add_new_cords_to_queue(&queue, point);
		}
		queue = queue->next;
		ft_lstdelone(head, free);
	}
	return (0);
}

int get_stats(char c, t_stats *stats, t_point start, t_point size)
{
	t_error err;

	err = 0;
	err = !(c == '1' || c == 'C' || c == 'X' || c == '0' || c == 'P' || c == 'E') * INV_CHAR | err;
	err = ((start.y == 0 || start.y == size.y) && c != '1') * INV_EDGES | err;
	err = ((start.x == 0 || start.x == size.x) && c != '1') * INV_EDGES | err;
	err = (c == 'P' && stats->pc.x) * DOUBLE_PLAYER | err;
	if (!(start.x == 0 || start.x == size.x) && (start.y > 0 || start.y < size.y) && !err)
	{
		stats->nenemy += (c == 'X');
		stats->nclc += (c == 'C');
		stats->next += (c == 'E');
		if (c == 'P')
		{
			stats->pc.x = (c == 'P') * start.x | stats->pc.x;
			stats->pc.y = (c == 'P') * start.y | stats->pc.y;
		}
	}
	return err;
}

t_error	scan_map(t_map *map, t_point start)
{
	while (map->arr[start.y] && !map->err)
	{
		start.x = 0;
		while (map->arr[start.y][start.x] && !map->err)
		{
			map->err = get_stats(map->arr[start.y][start.x], &map->stats, start, map->size);
			start.x += 1;
		}
		start.y += 1;
	}
	return (map->err);
}
