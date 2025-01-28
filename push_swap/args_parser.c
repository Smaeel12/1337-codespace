/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 16:57:02 by iboubkri          #+#    #+#             */
/*   Updated: 2025/01/27 20:22:21 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <stdio.h>
#include <stdlib.h>

static int	count_args(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == '+' || line[i] == '-')
			i++;
		if (line[i] < '0' || line[i] > '9')
			return (-1);
		while (line[i] >= '0' && line[i] <= '9')
			i++;
		count++;
		while (line[i] == ' ')
			i++;
	}
	return (count);
}

static int	join_args(char **line, char **av)
{
	int	i;

	i = 0;
	*line = ft_strdup(av[i++]);
	while (av[i])
	{
		*line = ft_strcat(*line, av[i]);
		i++;
	}
	return (count_args(*line));
}

static long	get_num(char *line, int len)
{
	int		i;
	char	*tmp;
	long	num;

	i = 0;
	tmp = (char *)malloc(len + 1);
	while (i < len && line[i])
	{
		tmp[i] = line[i];
		i++;
	}
	tmp[i] = '\0';
	num = ft_atol(tmp);
	free(tmp);
	return (num);
}

static void	split_args(t_stks *stks, char *args, int count)
{
	int		i;
	int		k;
	long	num;

	i = 0;
	k = 0;
	while (args[i])
	{
		while (args[k] && args[k] != ' ')
			k++;
		num = get_num(args + i, k);
		if (num < INT_MIN || num > INT_MAX)
		{
			free(args);
			ft_exit_error(stks);
		}
		stks->a.content[--count] = num;
		stks->meta.content[count] = num;
		stks->a.len += 1;
		while (args[k] && args[k] == ' ')
			k++;
		i = k;
	}
}

int	ft_init_stacks(t_stks *stks, char **av)
{
	char	*args;
	int		count;

	count = join_args(&args, av);
	stks->a.content = (int *)malloc(count * sizeof(int));
	stks->b.content = (int *)malloc(count * sizeof(int));
	stks->meta.content = (int *)malloc(count * sizeof(int));
	stks->a.len = 0;
	stks->b.len = 0;
	stks->meta.len = count;
	if (!stks->a.content || !stks->b.content || !stks->meta.content)
		ft_exit_error(stks);
	split_args(stks, args, count);
	if (ft_check_double(stks->a))
		ft_exit_error(stks);
	free(args);
	return (count);
}
