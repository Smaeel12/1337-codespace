/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:00:11 by iboubkri          #+#    #+#             */
/*   Updated: 2025/01/28 10:28:50 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

void	execute_line(t_stks *stks, char *line, int slen)
{
	int	res;

	res = 0;
	res += swapper(stks, 1 << ft_strcmp(line, "sa\n") | 1 << (2
				* ft_strcmp(line, "sb\n")) | 1 << (3 * ft_strcmp(line,
					"ss\n")));
	res += pusher(stks, 1 << ft_strcmp(line, "pa\n") | 1 << (2 * ft_strcmp(line,
					"pb\n")), slen);
	res += rotater(stks, 1 << ft_strcmp(line, "ra\n") | 1 << (2
				* ft_strcmp(line, "rb\n")) | 1 << (3 * ft_strcmp(line,
					"rr\n")));
	res += reverse_rotater(stks, 1 << ft_strcmp(line, "rra\n") | 1 << (2
				* ft_strcmp(line, "rrb\n")) | 1 << (3 * ft_strcmp(line,
					"rrr\n")));
	if (res == 0)
		ft_exit_error(stks);
}


int	main(int ac, char **av)
{
	char	*line;
	t_stks	*stks;
	int		slen;

	stks = (t_stks *)malloc(sizeof(t_stks));
	if (ac >= 2)
	{
		slen = ft_init_stacks(stks, &av[1]);
		while (1)
		{
			line = get_next_line(0);
			if (!line)
				break ;
			execute_line(stks, line, slen);
		}
		if (ft_is_sorted(stks->a) && !stks->b.len)
			write(1, "OK\n", 3);
		else
			write(1, "KO\n", 3);
	}
	free(stks->a.content);
	free(stks->b.content);
	free(stks->meta.content);
	free(stks);
}
