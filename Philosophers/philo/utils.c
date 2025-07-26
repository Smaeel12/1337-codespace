/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:11:57 by iboubkri          #+#    #+#             */
/*   Updated: 2025/04/17 00:16:34 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static size_t	to_number(char *input)
{
	size_t	prev;
	size_t	res;
	int		sign;

	res = 0;
	sign = 1;
	if (!input || !*input)
		return (res);
	while (*input == ' ' || (*input >= '\t' && *input <= '\r'))
		input++;
	if (*input == '-' || *input == '+')
		sign = ',' - *input++;
	while (*input)
	{
		prev = res;
		res = (res << 3) + (res << 1) + (*input - '0');
		if (res < prev || !(*input >= '0' && *input <= '9') || res > INT_MAX)
			return (0);
		input++;
	}
	return (res * (sign == 1));
}

int	parsing_input(t_data *data, char **argv)
{
	size_t	error;
	char	**message;

	message = (char *[]){
		"Error:\n\tnumber of times each philosopher must eat should be bigger \
than zero\n",
		"Error:\n\tnumber of philosophers should be bigger than zero (no more \
than 200)\n",
		"Error:\n\ttime to die should be bigger than zero\n",
		"Error:\n\ttime to eat should be bigger than zero\n",
		"Error:\n\ttime to sleep should be bigger than zero\n",
	};
	data->nb_philos = to_number(argv[0]);
	data->die_time = to_number(argv[1]);
	data->eat_time = to_number(argv[2]);
	data->sleep_time = to_number(argv[3]);
	data->total_eat = to_number(argv[4]);
	error = (!data->nb_philos * 1) + (!data->die_time * 2) + (!data->eat_time
			* 3) + (!data->sleep_time * 4) + ((argv[4] && !data->total_eat)
			* 5);
	if (error)
		return (write(2, message[error % 5], ft_strlen(message[error % 5])), 1);
	return (0);
}

size_t	ft_strlen(char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

int	join_philosophers(t_philo *philos, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	free(philos);
	return (0);
}

int	destroy_mutexes(t_data *data, t_fork *forks)
{
	size_t	i;

	i = 0;
	pthread_mutex_destroy(&data->read_lock);
	pthread_mutex_destroy(&data->write_lock);
	while (i < data->nb_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	free(forks);
	return (0);
}
