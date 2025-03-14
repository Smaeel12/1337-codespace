/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_controls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:14:19 by iboubkri          #+#    #+#             */
/*   Updated: 2025/03/14 14:25:32 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/main.h"

void	print(t_point *p)
{
	printf("%i || %i\n", p->x, p->y);
}

int	eliminate_a_collectible(t_list **head, int x, int y)
{
	t_list	*current;
	t_list	*prev;

	prev = NULL;
	if (!(*head))
		return (0);
	current = *head;
	while (current)
	{
		if (((t_point *)current->content)->x == x
			&& ((t_point *)current->content)->y == y)
		{
			if (prev)
				prev->next = current->next;
			else
				*head = current->next;
			ft_lstdelone(current, free);
			return (1);
		}
		prev = current;
		current = current->next;
	}
	return (0);
}

int	move_player(t_mlx *mlx, int x, int y)
{
	char	*c;

	c = &mlx->map.grid[mlx->map.stats.player_pos.y
		+ y][mlx->map.stats.player_pos.x + x];
	if (mlx->pc_anim.offset.x || mlx->pc_anim.offset.y)
		return (0);
	if (*c == '1' || (*c == 'E' && ft_lstsize(mlx->map.stats.clc_poss)))
		return (0);
	else if (*c == 'C')
	{
		eliminate_a_collectible(&mlx->map.stats.clc_poss,
			mlx->map.stats.player_pos.x + x, mlx->map.stats.player_pos.y + y);
		if (!ft_lstsize(mlx->map.stats.clc_poss))
			put_image(mlx, mlx->assets.exit.frames[1], mlx->map.stats.exit_pos.x
				* SIZE, mlx->map.stats.exit_pos.y * SIZE);
		put_image(mlx, mlx->assets.space.frames[0], (mlx->map.stats.player_pos.x
				+ x) * SIZE, (mlx->map.stats.player_pos.y + y) * SIZE);
	}
	mlx->err = (*c == 'E' && !ft_lstsize(mlx->map.stats.clc_poss)) * SUCCESS;
	mlx->err = (*c == 'X') * FAILED | mlx->err;
	mlx->pc_anim.direction = (t_point){x, y};
	return (0);
}
