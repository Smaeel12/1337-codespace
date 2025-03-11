/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 21:53:58 by iboubkri          #+#    #+#             */
/*   Updated: 2025/03/10 22:14:45 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

static char **list_to_grid(t_list *lst)
{
	char **grid;
	int i;

	grid = (char **)malloc((ft_lstsize(lst) + 1) * sizeof(char *));
	i = 0;
	while (grid && lst)
	{
		grid[i] = ft_strdup(lst->content);
		lst = lst->next;
		i++;
	}
	grid[i] = NULL;
	return (grid);
}

static t_point *new_cords(t_point cords)
{
	t_point *new;

	new = (t_point *)malloc(sizeof(t_point));
	new->x = cords.x;
	new->y = cords.y;
	return (new);
}

static int add_new_cords_to_queue(t_list **queue, t_point point)
{
	ft_lstadd_back(queue, ft_lstnew(new_cords((t_point){point.x + 1,
														point.y})));
	ft_lstadd_back(queue, ft_lstnew(new_cords((t_point){point.x - 1,
														point.y})));
	ft_lstadd_back(queue, ft_lstnew(new_cords((t_point){point.x, point.y + 1})));
	ft_lstadd_back(queue, ft_lstnew(new_cords((t_point){point.x, point.y - 1})));
	return (0);
}

static t_point search_path(char **grid, t_point start)
{
	t_list *queue;
	t_list *head;
	t_point point;
	t_point count;

	queue = NULL;
	count = (t_point){0};
	ft_lstadd_back(&queue, ft_lstnew(new_cords(start)));
	head = queue;
	while (queue)
	{
		point = *((t_point *)queue->content);
		if (grid[point.y][point.x] != '1' && grid[point.y][point.x] != 'X' && grid[point.y][point.x] != 'F')
		{
			count.x += (grid[point.y][point.x] == 'C'); /* Collectibles */
			count.y += (grid[point.y][point.x] == 'E'); /* Exits */
			grid[point.y][point.x] = 'F';
			add_new_cords_to_queue(&queue, point);
		}
		queue = queue->next;
	}
	return (ft_lstclear(&head, free), clear_grid(grid), count);
}
static int scan_map(t_stats *stats, char **grid, t_point size, t_point id)
{
	id.y = 0;
	while (grid && grid[id.y] && !stats->err)
	{
		id.x = 0;
		while (grid[id.y][id.x] && !stats->err)
		{
			stats->err = ((id.x == 0 || id.y == 0 || id.x == size.x || id.y == size.y) && grid[id.y][id.x] != '1') * INV_EDGES;
			if (grid[id.y][id.x] == 'P' && !stats->err)
				ft_lstadd_back(&stats->player_pos, ft_lstnew(new_cords(id)));
			else if (grid[id.y][id.x] == 'E' && !stats->err)
				ft_lstadd_back(&stats->exit_pos, ft_lstnew(new_cords(id)));
			else if (grid[id.y][id.x] == 'C' && !stats->err)
				ft_lstadd_back(&stats->clc_poss, ft_lstnew(new_cords(id)));
			else if (grid[id.y][id.x] == 'X' && !stats->err)
				ft_lstadd_back(&stats->enm_poss, ft_lstnew(new_cords(id)));
			else if (grid[id.y][id.x] != '0' && grid[id.y][id.x] != '1')
				stats->err = INV_CHAR;
			id.x += 1;
		}
		id.y += 1;
	}
	stats->err = (!ft_lstsize(stats->clc_poss) || ft_lstsize(stats->exit_pos) != 1 || !ft_lstsize(stats->player_pos)) * INV_STATS;
	return (stats->err);
}

static t_list *extract_map(t_map *map, int fd)
{
	t_list *lst;
	char *line;

	lst = NULL;
	line = get_next_line(fd);
	if (!line)
		return (map->err = EMPTY_FILE, NULL);
	map->size.x = ft_strlen(line) - 1;
	while (line)
	{
		if ((ft_strlen(line) - !(!ft_strchr(line, '\n'))) != map->size.x)
			map->err = NOT_RECT_MAP;
		ft_lstadd_back(&lst, ft_lstnew(ft_substr(line, 0, map->size.x)));
		free(line);
		line = get_next_line(fd);
		map->size.y += 1;
	}
	if (map->size.y < 3 || map->err)
		return (map->err = NOT_RECT_MAP, ft_lstclear(&lst, free), NULL);
	return (lst);
}

t_map load_map(int fd)
{
	t_map map;
	t_list *lst;
	t_point stats;

	map = (t_map){NULL};
	lst = extract_map(&map, fd);
	if (!lst || map.err)
		return (clear_map(&map), exit(1), map);
	map.grid = list_to_grid(lst);
	map.stats.err = scan_map(&map.stats, map.grid, map.size, (t_point){0});
	if (map.stats.err)
		return (ft_lstclear(&lst, free), clear_map(&map), exit(1), map);
	stats = search_path(list_to_grid(lst), *((t_point *)map.stats.player_pos->content));
	map.stats.err = ((int)stats.x != ft_lstsize(map.stats.clc_poss) || stats.y != 1) * INV_REACH;
	if (map.stats.err)
		return (ft_lstclear(&lst, free), clear_map(&map), exit(1), map);
	return (ft_lstclear(&lst, free), map);
}
