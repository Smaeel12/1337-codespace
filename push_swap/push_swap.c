/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 10:14:38 by iboubkri          #+#    #+#             */
/*   Updated: 2025/01/30 10:37:21 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	sort_small_stack(t_stks *stks)
{
	int	i;
	int	j;

	i = 0;
	while (!ft_is_sorted(stks->a) && i < stks->meta.len / 2 && stks->a.len > 3)
	{
		j = 0;
		while (stks->a.content[j] != stks->meta.content[i])
			j++;
		ft_get_to_top(stks->a, j, "ra\n", "rra\n");
		push_stack(&stks->b, &stks->a, "pb\n");
		i++;
	}
	while (!ft_is_sorted(stks->a) || stks->b.len)
	{
		if (stks->a.content[1] > stks->a.content[0])
			reverse_rotate_stack(stks->a, "rra\n");
		else if (stks->a.content[stks->a.len - 1] > stks->a.content[stks->a.len
				- 2])
			swap_stack(stks->a, "sa\n");
		else
			push_stack(&stks->b, &stks->a, "pb\n");
		while (ft_is_sorted(stks->a) && stks->b.len)
			push_stack(&stks->a, &stks->b, "pa\n");
	}
}

static void	execute_large_stack_sort(t_stks *stks, int end)
{
	int	start;

	start = 0;
	while (stks->a.len)
	{
		if (stks->a.content[stks->a.len - 1] <= stks->meta.content[end])
		{
			push_stack(&stks->b, &stks->a, "pb\n");
			if (stks->b.len > 1)
			{
				if (stks->b.content[stks->b.len
						- 1] <= stks->meta.content[start])
					rotate_stack(stks->b, "rb\n");
				else if (stks->b.content[stks->b.len
						- 1] < stks->b.content[stks->b.len - 2])
					swap_stack(stks->b, "sb\n");
			}
			if (start < end)
				start++;
			if (end < stks->meta.len - 1)
				end++;
		}
		else
			rotate_stack(stks->a, "ra\n");
	}
}

static void	sort_large_stack(t_stks *stks)
{
	int	max;
	int	end;

	end = 0;
	if (stks->a.len <= 100)
		end = stks->a.len / 7;
	else if (stks->a.len > 100)
		end = stks->a.len / 13;
	execute_large_stack_sort(stks, end);
	while (stks->b.len)
	{
		max = ft_get_max_pos(stks->b);
		ft_get_to_top(stks->b, max, "rb\n", "rrb\n");
		push_stack(&stks->a, &stks->b, "pa\n");
	}
}

static void	sort_meta_array(t_stack *meta)
{
	int	i;
	int	j;
	int	tmp;

	i = 0;
	j = 0;
	while (i < meta->len)
	{
		j = i + 1;
		while (j < meta->len)
		{
			if (meta->content[i] > meta->content[j])
			{
				tmp = meta->content[i];
				meta->content[i] = meta->content[j];
				meta->content[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

int	main(int ac, char **av)
{
	t_stks	*stks;

	stks = (t_stks *)malloc(sizeof(t_stks));
	if (ac >= 2)
	{
		ft_init_stacks(stks, &av[1]);
		if (stks->a.len > 1 && !ft_is_sorted(stks->a))
		{
			sort_meta_array(&stks->meta);
			if (stks->a.len > 10)
				sort_large_stack(stks);
			else
				sort_small_stack(stks);
		}
	}
	free(stks->a.content);
	free(stks->b.content);
	free(stks->meta.content);
	free(stks);
}
