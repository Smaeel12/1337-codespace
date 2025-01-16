/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 10:59:10 by iboubkri          #+#    #+#             */
/*   Updated: 2025/01/16 11:38:59 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

long	ft_atol(const char *str)
{
	size_t	i;
	size_t	res;
	int		sign;

	i = 0;
	res = 0;
	sign = 1;
	while (((str[i] >= 9 && str[i] <= 13) || str[i] == ' '))
		i++;
	if ((str[i] == '-' || str[i] == '+'))
		sign = (44 - str[i++]);
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (str[i] - '0') + res * 10;
		i++;
	}
	return ((int)(res * sign));
}

int ft_isdigit(char *str) {
    int i;

    i = 0;
	if ((str[i] == '-' || str[i] == '+'))
		i++;
	while (str[i])
	{
		if (str[i] < '0' && str[i] > '9')
            return 0;
	}
    return 1;
}

int count_args(char **args) {
    int i;

    i = 0;
    while (args[i])
        i++;
    return i;
}

int process_args(t_stack *stack, char **args) {
    int i;
    int num;

    i = 0;
    stack->len = count_args(args);
    stack->content = malloc(stack->len * sizeof(int));
    while (args[i])
    {
        num = ft_atol(args[i]);
        if (num == 0 && !ft_isdigit(args[i]))
                return 0;
        stack->content[i] = num;
    }
    return 1;
}