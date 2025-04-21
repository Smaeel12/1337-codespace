/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:53:50 by iboubkri          #+#    #+#             */
/*   Updated: 2025/04/21 17:24:36 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	display_message(t_philo *philo, char *action)
{
	sem_wait(philo->read_lock);
	if (philo->is_dead)
	{
		sem_post(philo->read_lock);
		return (0);
	}
	sem_wait(philo->data->write_lock);
	printf("%li %li %s\n", (getcurrenttime() - philo->data->start_time),
		philo->id, action);
	sem_post(philo->data->write_lock);
	sem_post(philo->read_lock);
	return (1);
}

static void	*philo_routine(t_philo *philo)
{
	while (display_message(philo, "is thinking"))
	{
		ft_msleep(philo->think_time);
		if (philo->data->nb_philos == 1)
			return (0);
		sem_wait(philo->data->forks_lock);
		sem_wait(philo->data->forks_lock);
		{
			display_message(philo, "has taken a fork");
			display_message(philo, "has taken a fork");
			sem_wait(philo->read_lock);
			philo->nb_meals += 1;
			philo->last_meal = getcurrenttime();
			sem_post(philo->read_lock);
			display_message(philo, "is eating");
			ft_msleep(philo->data->eat_time);
		}
		sem_post(philo->data->forks_lock);
		sem_post(philo->data->forks_lock);
		display_message(philo, "is sleeping");
		ft_msleep(philo->data->sleep_time);
		philo->think_time = (philo->data->die_time - (getcurrenttime()
					- philo->last_meal)) * 0.2;
	}
	return (NULL);
}

static int	start_philosopher(t_philo *philo, t_data *data)
{
	pthread_t	thread;

	if (pthread_create(&thread, NULL, (void *(*)(void *))philo_routine, philo))
		return (write(2, TCREAT_FAILED, ft_strlen(TCREAT_FAILED)), exit(1), 1);
	while (!sem_wait(philo->read_lock))
	{
		philo->is_dead = (getcurrenttime() - philo->last_meal >= data->die_time)
			| ((philo->nb_meals >= data->total_eat) && data->total_eat) << 1;
		if (philo->is_dead)
		{
			if (philo->is_dead == 1)
			{
				sem_wait(data->write_lock);
				printf("%li %li died\n", (getcurrenttime() - data->start_time),
					philo->id);
				sem_post(data->death_lock);
			}
			sem_post(philo->read_lock);
			break ;
		}
		sem_post(philo->read_lock);
		usleep(1000);
	}
	return (pthread_join(thread, NULL), 0);
}

char	*create_name(size_t id)
{
	char	*name;
	size_t	i;

	i = 0;
	name = (char *)malloc(MAX_NAME_LEN * sizeof(char));
	memset(name, 0, MAX_NAME_LEN);
	while (i < 10)
	{
		name[i] = SEM_READ[i];
		i++;
	}
	while (i < MAX_NAME_LEN && id)
	{
		name[i] = '0' + id % 10;
		id /= 10;
		i++;
	}
	name[MAX_NAME_LEN - 1] = '\0';
	sem_unlink(name);
	return (name);
}

int	create_philosophers(t_data *data)
{
	t_philo	philo;
	size_t	i;

	i = -1;
	data->start_time = getcurrenttime();
	while (++i < data->nb_philos)
	{
		data->pids[i] = fork();
		if (data->pids[i] < 0)
			return (1);
		if (data->pids[i] == 0)
		{
			philo = (t_philo){++i, 0, getcurrenttime(), 0, 0, data, NULL, NULL};
			philo.name = create_name(philo.id);
			philo.read_lock = sem_open(philo.name, O_CREAT, 0664, 1);
			if (philo.read_lock == SEM_FAILED)
				return (write(2, SOPEN_ERR, ft_strlen(SOPEN_ERR)), exit(1), 1);
			sem_wait(philo.data->death_lock);
			start_philosopher(&philo, data);
			sem_close(philo.read_lock);
			sem_unlink(philo.name);
			return (clear_data(data), free(philo.name), exit(0), 1);
		}
	}
	return (0);
}
