/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 11:34:30 by iboubkri          #+#    #+#             */
/*   Updated: 2025/02/06 13:24:58 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	ft_exit_error(t_stks *stks)
{
	write(2, "Error\n", 6);
	free(stks->a.content);
	free(stks->b.content);
	free(stks->meta.content);
	free(stks);
	exit(1);
}

int	ft_is_sorted(t_stack stack)
{
	int	i;

	i = 0;
	while (i < stack.len - 1)
	{
		if (stack.content[i] < stack.content[i + 1])
			return (0);
		i++;
	}
	return (1);
}

int	ft_get_max_pos(t_stack stack)
{
	int	i;
	int	pos;

	i = 0;
	pos = 0;
	while (i < stack.len)
	{
		if (stack.content[pos] < stack.content[i])
			pos = i;
		i++;
	}
	return (pos);
}

void	ft_get_to_top(t_stack stack, int pos, char *r, char *rr)
{
	if (pos >= stack.len / 2)
	{
		while (pos++ < stack.len - 1)
			rotate_stack(stack, r);
	}
	else if (pos < stack.len / 2)
	{
		while (pos-- >= 0)
			reverse_rotate_stack(stack, rr);
	}
}

int	ft_check_double(t_stack stack)
{
	int	i;
	int	j;

	i = 0;
	while (i < stack.len - 1)
	{
		j = i + 1;
		while (j < stack.len)
		{
			if (stack.content[i] == stack.content[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
