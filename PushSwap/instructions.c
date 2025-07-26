/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 12:02:36 by iboubkri          #+#    #+#             */
/*   Updated: 2025/01/27 14:24:44 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	push_stack(t_stack *to, t_stack *from, char *action)
{
	if (action)
		write(1, action, 3);
	to->content[to->len] = from->content[from->len - 1];
	to->len++;
	from->len--;
}

void	reverse_rotate_stack(t_stack stack, char *action)
{
	int	i;
	int	tmp;

	if (action)
		write(1, action, 4);
	i = 0;
	tmp = stack.content[0];
	while (i < stack.len - 1)
	{
		stack.content[i] = stack.content[i + 1];
		i++;
	}
	stack.content[stack.len - 1] = tmp;
}

void	rotate_stack(t_stack stack, char *action)
{
	int	i;
	int	tmp;

	if (action)
		write(1, action, 3);
	i = stack.len - 1;
	tmp = stack.content[i];
	while (i > 0)
	{
		stack.content[i] = stack.content[i - 1];
		i--;
	}
	stack.content[0] = tmp;
}

void	swap_stack(t_stack stack, char *action)
{
	int	tmp;

	if (action)
		write(1, action, 3);
	tmp = stack.content[stack.len - 1];
	stack.content[stack.len - 1] = stack.content[stack.len - 2];
	stack.content[stack.len - 2] = tmp;
}
