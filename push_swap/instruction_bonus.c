/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:09:49 by iboubkri          #+#    #+#             */
/*   Updated: 2025/01/28 10:10:12 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	swapper(t_stks *stks, int move)
{
	if (move == 3)
	{
		if (stks->a.len < 2)
			return (0);
		swap_stack(stks->a, NULL);
	}
	else if (move == 5)
	{
		if (stks->b.len < 2)
			return (0);
		swap_stack(stks->b, NULL);
	}
	else if (move == 9)
	{
		if (stks->a.len < 2 || stks->b.len < 2)
			return (0);
		swap_stack(stks->a, NULL);
		swap_stack(stks->b, NULL);
	}
	return (1);
}

int	pusher(t_stks *stks, int move, int slen)
{
	if (move == 3)
	{
		if (stks->a.len >= slen)
			return (0);
		push_stack(&stks->a, &stks->b, NULL);
	}
	if (move == 5)
	{
		if (stks->b.len >= slen)
			return (0);
		push_stack(&stks->b, &stks->a, NULL);
	}
	return (1);
}

int	rotater(t_stks *stks, int move)
{
	if (move == 3)
		rotate_stack(stks->a, NULL);
	else if (move == 5)
		rotate_stack(stks->b, NULL);
	else if (move == 9)
	{
		rotate_stack(stks->a, NULL);
		rotate_stack(stks->b, NULL);
	}
	return (1);
}

int	reverse_rotater(t_stks *stks, int move)
{
	if (move == 3)
		reverse_rotate_stack(stks->a, NULL);
	else if (move == 5)
		reverse_rotate_stack(stks->b, NULL);
	else if (move == 9)
	{
		reverse_rotate_stack(stks->a, NULL);
		reverse_rotate_stack(stks->b, NULL);
	}
	return (1);
}
