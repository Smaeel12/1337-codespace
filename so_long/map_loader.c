/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:24:01 by iboubkri          #+#    #+#             */
/*   Updated: 2025/03/14 13:52:08 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/main.h"

static char	**list_to_grid(t_list *lst)
{
	char	**grid;
	int		i;

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

static t_list	*extract_map(t_map *map, int fd)
{
	t_list	*lst;
	char	*line;

	lst = NULL;
	line = get_next_line(fd);
	if (!line)
		return (map->err = EMPTY_FILE, lst);
	map->size.x = ft_strlen(line) - 1;
	while (line)
	{
		if ((int)(ft_strlen(line) - !(!ft_strchr(line, '\n'))) != map->size.x)
			map->err = NOT_RECT_MAP;
		ft_lstadd_back(&lst, ft_lstnew(ft_substr(line, 0, map->size.x)));
		free(line);
		line = get_next_line(fd);
		map->size.y += 1;
	}
	if (map->size.y < 3)
		return (map->err = NOT_RECT_MAP, lst);
	return (lst);
}

static int	validate_map(t_mlx *mlx, t_list *lst)
{
	char	**temp;
	t_point	path_stats;

	path_stats = (t_point){0};
	mlx->map.grid = list_to_grid(lst);
	scan_map(&mlx->map.stats, mlx->map.grid, mlx->map.size, (t_point){0});
	if (mlx->map.stats.err)
		return (ft_lstclear(&lst, free), exit_program(mlx), 1);
	if (!mlx->map.stats.player_pos.x || !mlx->map.stats.exit_pos.x
		|| ft_lstsize(mlx->map.stats.clc_poss) < 1)
		return (mlx->map.err = INV_STATS, 1);
	temp = list_to_grid(lst);
	search_path(temp, mlx->map.stats.player_pos, mlx->map.size, &path_stats);
	if (path_stats.y != ft_lstsize(mlx->map.stats.clc_poss)
		|| path_stats.x != 1)
		return (free2(temp), mlx->map.err = INV_REACH, 1);
	free2(temp);
	return (0);
}

int	load_map(t_mlx *mlx, int fd)
{
	t_list	*lst;

	mlx->map = (t_map){NULL, {NULL, NULL, {0, 0}, {0, 0}, 0}, {0, 0}, 0};
	lst = extract_map(&mlx->map, fd);
	if (mlx->map.err)
		return (ft_lstclear(&lst, free), exit_program(mlx));
	validate_map(mlx, lst);
	ft_lstclear(&lst, free);
	if (mlx->map.err)
		return (exit_program(mlx));
	return (mlx->map.err);
}
