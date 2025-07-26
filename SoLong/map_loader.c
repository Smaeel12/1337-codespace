/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:24:01 by iboubkri          #+#    #+#             */
/*   Updated: 2025/03/18 22:22:58 by iboubkri         ###   ########.fr       */
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
	return (lst);
}

static int	validate_map(t_mlx *mlx, t_list *lst)
{
	t_point	path_stats;
	char	**temp;
	int		err;

	path_stats = (t_point){0};
	mlx->map.grid = list_to_grid(lst);
	err = scan_map(&mlx->map.cords, mlx->map.grid, mlx->map.size);
	if (err)
		return (mlx->map.err = err, 1);
	err = !ft_lstsize(mlx->map.cords.clc) * COINS_ERR | err;
	err = (ft_lstsize(mlx->map.cords.exit) != 1) * EXIT_ERR | err;
	err = (ft_lstsize(mlx->map.cords.player) != 1) * PLAYER_ERR | err;
	if (err)
		return (mlx->map.err = err, 1);
	temp = list_to_grid(lst);
	search_path(temp, *((t_point *)mlx->map.cords.player->content),
		mlx->map.size, &path_stats);
	free2(temp);
	if ((path_stats.y != ft_lstsize(mlx->map.cords.clc)) || path_stats.x != 1)
		return (mlx->map.err = PATH_ERR, 1);
	return (0);
}

int	load_map(t_mlx *mlx, int fd)
{
	t_list	*lst;

	lst = extract_map(&mlx->map, fd);
	if (mlx->map.err)
		return (ft_lstclear(&lst, free), exit_program(mlx));
	validate_map(mlx, lst);
	ft_lstclear(&lst, free);
	if (mlx->map.err)
		exit_program(mlx);
	return (0);
}
