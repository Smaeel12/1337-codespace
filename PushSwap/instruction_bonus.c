/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:09:49 by iboubkri          #+#    #+#             */
/*   Updated: 2025/02/06 13:37:11 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	swapper(t_stks *stks, int move)
{
	if (move == 3)
	{
		if (stks->a.len > 1)
			swap_stack(stks->a, NULL);
		return (1);
	}
	else if (move == 5)
	{
		if (stks->b.len > 1)
			swap_stack(stks->b, NULL);
		return (1);
	}
	else if (move == 9)
	{
		if (stks->a.len > 1 && stks->b.len > 1)
		{
			swap_stack(stks->a, NULL);
			swap_stack(stks->b, NULL);
		}
		return (1);
	}
	return (0);
}

int	pusher(t_stks *stks, int move, int slen)
{
	if (move == 3)
	{
		if (stks->a.len < slen)
			push_stack(&stks->a, &stks->b, NULL);
		return (1);
	}
	if (move == 5)
	{
		if (stks->b.len < slen)
			push_stack(&stks->b, &stks->a, NULL);
		return (1);
	}
	return (0);
}

int	rotater(t_stks *stks, int move)
{
	if (move == 3)
	{
		if (stks->a.len > 1)
			rotate_stack(stks->a, NULL);
		return (1);
	}
	else if (move == 5)
	{
		if (stks->b.len > 1)
			rotate_stack(stks->b, NULL);
		return (1);
	}
	else if (move == 9)
	{
		if (stks->a.len > 1 && stks->b.len > 1)
		{
			rotate_stack(stks->a, NULL);
			rotate_stack(stks->b, NULL);
		}
		return (1);
	}
	return (0);
}

int	reverse_rotater(t_stks *stks, int move)
{
	if (move == 3)
	{
		if (stks->a.len > 1)
			reverse_rotate_stack(stks->a, NULL);
		return (1);
	}
	else if (move == 5)
	{
		if (stks->b.len > 1)
			reverse_rotate_stack(stks->b, NULL);
		return (1);
	}
	else if (move == 9)
	{
		if (stks->a.len > 1 && stks->b.len > 1)
		{
			reverse_rotate_stack(stks->a, NULL);
			reverse_rotate_stack(stks->b, NULL);
		}
		return (1);
	}
	return (0);
}
