/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:24:01 by iboubkri          #+#    #+#             */
/*   Updated: 2025/03/02 21:44:11 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/main.h"

static char	**list_to_array(t_list *lst, int size)
{
	char	**arr;
	int		i;

	i = 0;
	arr = (char **)malloc((size + 1) * sizeof(char *));
	while (i < size)
	{
		arr[i++] = ft_strdup(lst->content);
		lst = lst->next;
	}
	arr[i] = NULL;
	return (arr);
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

t_error	add_assets_positons(t_mlx *mlx)
{
	t_point	start;
	int		clc_idx;
	int		enm_idx;

	start = (t_point){0};
	clc_idx = 0;
	enm_idx = 0;
	mlx->map.stats.clc_poss = (t_point *)malloc(mlx->map.stats.nclc * sizeof(t_point));
	mlx->map.stats.enemy_poss = (t_point *)malloc(mlx->map.stats.nenemy * sizeof(t_point));
	while (mlx->map.arr[start.y] && !mlx->map.err)
	{
		start.x = 0;
		while (mlx->map.arr[start.y][start.x] && !mlx->map.err)
		{
			if (mlx->map.arr[start.y][start.x] == 'C')
			{
				mlx->map.stats.clc_poss[clc_idx] = start;
				clc_idx++;
			}
			if (mlx->map.arr[start.y][start.x] == 'X')
			{
				mlx->map.stats.enemy_poss[enm_idx] = start;
				enm_idx++;
			}
			if (mlx->map.arr[start.y][start.x] == 'E')
				mlx->map.stats.exit_pos = start;
			start.x += 1;
		}
		start.y += 1;
	}
	return (mlx->map.err);
}

static int	validate_map(t_mlx *mlx, t_list *lst)
{
	t_map	origin;

	mlx->map.arr = list_to_array(lst, mlx->map.size.y);
	scan_map(&mlx->map, (t_point){0});
	if (mlx->map.err)
		return mlx->map.err;
	if (mlx->map.stats.pc.x == 0 || mlx->map.stats.pc.y == 0
		|| mlx->map.stats.nclc < 1 || mlx->map.stats.next != 1)
		return mlx->map.err = INV_STATS, 1;
	origin = mlx->map;
	mlx->map.arr = list_to_array(lst, mlx->map.size.y);
	mlx->map.stats = (t_stats){mlx->map.stats.pc, NULL, NULL, {0}, 0, 0, 0, mlx->map.stats.nenemy};
	search_path(&mlx->map, mlx->map.stats.pc, '1');
	if (mlx->map.stats.nclc != origin.stats.nclc || mlx->map.stats.next != 1)
		return (free_array(origin.arr), mlx->map.err = INV_REACH, 1);
	free_array(mlx->map.arr);
	mlx->map.arr = origin.arr;
	add_assets_positons(mlx);
	return (0);
}

int	load_map(t_mlx *mlx, int fd)
{
	t_list	*lst;

	mlx->map = (t_map){NULL};
	lst = extract_map(&mlx->map, fd);
	if (mlx->map.err)
		return (ft_lstclear(&lst, free), exit_program(mlx));
	validate_map(mlx, lst);
	ft_lstclear(&lst, free);
	if (mlx->map.err)
		return (exit_program(mlx));
	return (mlx->map.err);
}
