/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 14:50:32 by iboubkri          #+#    #+#             */
/*   Updated: 2025/04/02 16:49:28 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

static int to_number(char *input)
{
	unsigned int res;
	int sign;

	res = 0;
	sign = 1;
	while (*input == ' ' || (*input >= '\t' && *input <= '\r'))
		input++;
	if (*input == '-' || *input == '+')
		sign = ',' - *input++;
	while (*input >= '0' && *input <= '9')
	{
		res = (res << 3) + (res << 1) + (*input - '0');
		input++;
	}
	return (res * (sign > 0) * !(*input && (*input >= '0' || *input <= '9')));
}

int *parse_input(char **av)
{
	char **messages;
	int *data;
	int i;

	i = 0;
	messages = (char *[]){M1, M2, M3, M4, M5};
	data = (int *)malloc(5 * sizeof(int));
	memset(data, 0, 5 * sizeof(int));
	while (av[i])
	{
		data[i] = to_number(av[i]);
		if (!data[i])
			return (free(data), write(2, messages[i], ft_strlen(messages[i])), NULL);
		i++;
	}
	return data;
}

suseconds_t get_current_time(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int ft_strlen(char *str)
{
	int len;

	len = 0;
	while (str[len++])
		;
	return (len);
}
