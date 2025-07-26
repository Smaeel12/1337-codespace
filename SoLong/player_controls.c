/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_controls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:14:19 by iboubkri          #+#    #+#             */
/*   Updated: 2025/03/19 00:19:16 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/main.h"

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

int	move_player_frames(t_mlx *mlx, t_point *ppos, t_point move)
{
	put_image(mlx, *mlx->assets.space.frames, ppos);
	*ppos = (t_point){ppos->x + move.x, ppos->y + move.y};
	put_image(mlx, mlx->assets.player_walk[DOWN].frames[0], ppos);
	return (0);
}

int	move_player(t_mlx *mlx, t_point move)
{
	t_point	*ppos;

	ppos = mlx->map.cords.player->content;
	if (mlx->map.grid[ppos->y + move.y][ppos->x + move.x] == '1'
		|| (mlx->map.grid[ppos->y + move.y][ppos->x + move.x] == 'E'
			&& ft_lstsize(mlx->map.cords.clc)))
		return (0);
	if (mlx->map.grid[ppos->y + move.y][ppos->x + move.x] == 'C')
		eliminate_a_collectible(&mlx->map.cords.clc, ppos->x + move.x, ppos->y
			+ move.y);
	ft_printf("number of moves: %i\n", ++(*mlx).nmoves);
	if (mlx->map.grid[ppos->y + move.y][ppos->x + move.x] == 'E'
		&& !ft_lstsize(mlx->map.cords.clc))
		exit_program(mlx);
	put_image(mlx, mlx->assets.exit.frames[!ft_lstsize(mlx->map.cords.clc)],
		mlx->map.cords.exit->content);
	mlx->err = (mlx->map.grid[ppos->y + move.y][ppos->x + move.x] == 'X')
		* EXIT_SIG;
	mlx->map.grid[ppos->y + move.y][ppos->x + move.x] = 'P';
	mlx->map.grid[ppos->y][ppos->x] = '0';
	if (!BONUS_MODE)
		move_player_frames(mlx, ppos, move);
	return (mlx->player.side = (3 & move.x) | (2 & move.y),
		mlx->player.cur_frame = &mlx->assets.player_walk[mlx->player.side],
		mlx->player.direction = move, 0);
}

int	keypress(int keycode, t_mlx *mlx)
{
	if (keycode == ESCAPE)
		return (mlx->err = OK, exit_program(mlx));
	if (keycode == KEY_RIGHT && !((mlx->player.direction.x
				|| mlx->player.direction.y) && BONUS_MODE))
		return (move_player(mlx, (t_point){1, 0}));
	if (keycode == KEY_LEFT && !((mlx->player.direction.x
				|| mlx->player.direction.y) && BONUS_MODE))
		return (move_player(mlx, (t_point){-1, 0}));
	if (keycode == KEY_UP && !((mlx->player.direction.x
				|| mlx->player.direction.y) && BONUS_MODE))
		return (move_player(mlx, (t_point){0, -1}));
	if (keycode == KEY_DOWN && !((mlx->player.direction.x
				|| mlx->player.direction.y) && BONUS_MODE))
		return (move_player(mlx, (t_point){0, 1}));
	return (0);
}
