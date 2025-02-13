/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:24:01 by iboubkri          #+#    #+#             */
/*   Updated: 2025/02/13 10:19:50 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/main.h"

static int	extract_map(t_mlx *mlx, int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
		return (mlx->err = EMPTY_FILE, (1));
	mlx->map = (t_map){NULL, {ft_strlen(line) - 1, 0}, {0, 0}};
	mlx->stats = (t_stats){0, 0};
	while (line)
	{
		if ((ft_strlen(line) - !(!ft_strchr(line,
						'\n'))) != (size_t)mlx->map.msize.x)
			mlx->err = NOT_RECT_MAP;
		ft_lstadd_back(&mlx->map.map, ft_lstnew(ft_substr(line, 0,
					mlx->map.msize.x)));
		free(line);
		line = get_next_line(fd);
		mlx->map.msize.y += 1;
	}
	return (mlx->err = MAP_OK, (1));
}

static int	run_dfs_search(t_mlx *mlx, int fd)
{
	t_list	*origin;
	t_stats	stats;

	extract_map(mlx, fd);
	if (mlx->map.map == NULL || mlx->map.msize.y < MIN_MAP_HEIGHT || mlx->err)
		return (ft_lstclear(&mlx->map.map, free), mlx->err);
	origin = mlx->map.map;
	mlx->map.map = ft_lstcopy(origin);
	dfs_search(mlx, mlx->map.pp, 0);
	if (mlx->err || mlx->stats.nclc < 1 || mlx->stats.next != 1
		|| mlx->map.pp.x == 0)
		return (ft_lstclear(&origin, free), ft_lstclear(&mlx->map.map, free),
			1);
	stats = mlx->stats;
	ft_lstclear(&mlx->map.map, free);
	mlx->stats = (t_stats){0, 0};
	mlx->map.map = ft_lstcopy(origin);
	dfs_search(mlx, mlx->map.pp, '1');
	if (mlx->stats.nclc != stats.nclc || mlx->stats.next != stats.next)
		return (ft_lstclear(&origin, free), ft_lstclear(&mlx->map.map, free),
			mlx->err = MAP_INVALID, mlx->err);
	ft_lstclear(&mlx->map.map, free);
	return (mlx->stats = stats, mlx->map.map = origin, mlx->err = MAP_OK, 0);
}

int	check_map(t_mlx *mlx, char *filename)
{
	int	fd;

	if (!ft_strnstr(filename, ".ber", ft_strlen(filename)))
		return (mlx->err = INVALID_EXT, 1);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (mlx->err = FILE_NOT_FOUND, 1);
	run_dfs_search(mlx, fd);
	return (mlx->err);
}
