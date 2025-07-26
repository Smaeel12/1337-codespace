/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:11:57 by iboubkri          #+#    #+#             */
/*   Updated: 2025/04/18 19:09:02 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static size_t	to_number(char *input)
{
	size_t	res;
	int		sign;

	res = 0;
	sign = 1;
	if (!input || !*input)
		return (0);
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

int	parsing_data(char **argv, t_data *data)
{
	size_t	error;
	char	**message;

	memset(data, 0, sizeof(t_data));
	message = (char *[]){
		"Error:\n\tnumber of times each philosopher must eat should be bigger \
than zero\n",
		"Error:\n\tnumber of philosophers should be bigger than zero\n",
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

int	clear_data(t_data *data)
{
	free(data->pids);
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_WRITE);
	sem_unlink(SEM_DEATH);
	if (data->forks_lock)
		sem_close(data->forks_lock);
	if (data->write_lock)
		sem_close(data->write_lock);
	if (data->death_lock)
		sem_close(data->death_lock);
	return (0);
}

void	*kill_rotuine(t_data *data)
{
	size_t	i;

	i = 0;
	sem_wait(data->death_lock);
	while (data->pids && i < data->nb_philos)
	{
		kill(data->pids[i], SIGKILL);
		i++;
	}
	return (0);
}
