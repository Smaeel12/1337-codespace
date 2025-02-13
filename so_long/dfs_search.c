/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs_search.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:04:28 by iboubkri          #+#    #+#             */
/*   Updated: 2025/02/12 19:16:18 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/main.h"

static int	check_end(t_mlx *mlx, char *node, t_point start, char stop)
{
	return (start.x < 0 || start.x >= mlx->map.msize.x || start.y < 0
		|| start.y >= mlx->map.msize.y || node[start.x] == 'F'
		|| node[start.x] == stop);
}

static int	check_edge(t_mlx *mlx, char *node, t_point start)
{
	return ((start.x == 0 || start.x == mlx->map.msize.x - 1 || start.y == 0
			|| start.y == mlx->map.msize.y - 1) && node[start.x] != '1');
}

static int	check_char(t_mlx *mlx, char *node, t_point start)
{
	if (node[start.x] == 'C')
		mlx->stats.nclc += 1;
	else if (node[start.x] == 'E')
		mlx->stats.next += 1;
	else if (node[start.x] == 'P' && mlx->map.pp.x == 0)
	{
		mlx->map.pp.x = start.x;
		mlx->map.pp.y = start.y;
	}
	else if (node[start.x] != '1' && node[start.x] != '0')
		return (1);
	return (0);
}

int	dfs_search(t_mlx *mlx, t_point start, char s)
{
	t_list	*node;

	node = ft_get_node(mlx->map.map, start.y);
	if (!node || check_end(mlx, node->content, start, s))
		return (1);
	if (check_edge(mlx, node->content, start) || check_char(mlx, node->content,
			start))
		mlx->err = MAP_INVALID;
	((char *)node->content)[start.x] = 'F';
	dfs_search(mlx, (t_point){start.x + 1, start.y}, s);
	dfs_search(mlx, (t_point){start.x, start.y + 1}, s);
	dfs_search(mlx, (t_point){start.x - 1, start.y}, s);
	dfs_search(mlx, (t_point){start.x, start.y - 1}, s);
	return (0);
}
