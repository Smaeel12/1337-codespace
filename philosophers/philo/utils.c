/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:11:57 by iboubkri          #+#    #+#             */
/*   Updated: 2025/04/12 00:47:25 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int join_philosophers(t_philo *philos, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		philos[i].is_dead = true;
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	return (0);
}

suseconds_t getcurrenttime(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

size_t ft_strlen(char *str)
{
	size_t len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

static size_t to_number(char *input)
{
	size_t res;
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
	return (res * (sign == 1) * !*input);
}

t_data *parsing_input(char **argv)
{
	char **messages;
	t_data *data;
	size_t i;

	i = 0;
	messages = (char *[]){
		"Error:\n\tnumber of philosophers should be bigger than zero\n",
		"Error:\n\ttime to die should be bigger than zero\n",
		"Error:\n\ttime to eat should be bigger than zero\n",
		"Error:\n\ttime to sleep should be bigger than zero\n",
		"Error:\n\tnumber of times each philosopher must eat should be\
 bigger than zero\n"};
	data = (t_data *)malloc(5 * sizeof(t_data));
	memset(data, 0, 5 * sizeof(t_data));
	while (argv[i])
	{
		data[i] = to_number(argv[i]);
		if (!data[i])
			return (free(data), write(2, messages[i], ft_strlen(messages[i])),
					NULL);
		i++;
	}
	return (data);
}
