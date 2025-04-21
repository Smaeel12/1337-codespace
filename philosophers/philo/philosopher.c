/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 01:22:30 by iboubkri          #+#    #+#             */
/*   Updated: 2025/04/21 17:21:56 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	display_message(t_philo *philo, char *action)
{
	bool	is_dead;

	pthread_mutex_lock(&philo->data->read_lock);
	pthread_mutex_lock(&philo->data->write_lock);
	is_dead = philo->data->death_flag;
	if (is_dead == false)
		printf("%li %li %s\n", (getcurrenttime() - philo->data->start_time),
			philo->id, action);
	pthread_mutex_unlock(&philo->data->write_lock);
	pthread_mutex_unlock(&philo->data->read_lock);
	return (!is_dead);
}

static void	*thread_routine(t_philo *philo)
{
	while (display_message(philo, "is thinking") && philo->data->nb_philos > 1)
	{
		ft_msleep(philo->data, philo->think_time);
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
		{
			display_message(philo, "has taken a fork");
			display_message(philo, "has taken a fork");
			pthread_mutex_lock(&philo->data->read_lock);
			philo->last_meal = getcurrenttime();
			philo->nb_meals += 1;
			pthread_mutex_unlock(&philo->data->read_lock);
			display_message(philo, "is eating");
			ft_msleep(philo->data, philo->data->eat_time);
		}
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		display_message(philo, "is sleeping");
		ft_msleep(philo->data, philo->data->sleep_time);
		philo->think_time = (philo->data->die_time - (getcurrenttime()
					- philo->last_meal)) * 0.2;
	}
	return (NULL);
}

int	monitoring(t_philo *philos, t_data *data, size_t done, size_t id)
{
	while (!ft_msleep(data, 1))
	{
		id = 0;
		done = 0;
		while (id < data->nb_philos && !pthread_mutex_lock(&data->read_lock))
		{
			done += (philos[id].nb_meals >= data->total_eat) && data->total_eat;
			data->death_flag = (getcurrenttime() - philos[id].last_meal
					>= data->die_time) | ((done >= data->nb_philos) << 1);
			if (data->death_flag)
			{
				if (data->death_flag == 1 << 1)
					return (pthread_mutex_unlock(&data->read_lock), 0);
				pthread_mutex_lock(&data->write_lock);
				printf("%li %li died\n", (getcurrenttime() - data->start_time),
					philos[id].id);
				pthread_mutex_unlock(&data->write_lock);
				return (pthread_mutex_unlock(&data->read_lock), 0);
			}
			pthread_mutex_unlock(&data->read_lock);
			id++;
		}
	}
	return (0);
}

t_philo	*create_philosophers(t_fork *forks, t_data *data)
{
	t_philo	*philos;
	size_t	i;

	i = 0;
	data->death_flag = 0;
	data->start_time = getcurrenttime();
	philos = (t_philo *)malloc(data->nb_philos * sizeof(t_philo));
	if (!philos)
		return (write(2, MALLOC_ERR, ft_strlen(MALLOC_ERR)), NULL);
	while (i < data->nb_philos)
	{
		philos[i].id = i + 1;
		philos[i].left_fork = &forks[(!(i & 1) + i) % data->nb_philos];
		philos[i].right_fork = &forks[((i & 1) + i) % data->nb_philos];
		philos[i].last_meal = getcurrenttime();
		philos[i].think_time = 0;
		philos[i].nb_meals = 0;
		philos[i].data = data;
		if (pthread_create(&philos[i].thread, NULL,
				(void *(*)(void *))thread_routine, &philos[i]))
			return (free(philos), NULL);
		i++;
	}
	return (philos);
}

t_fork	*create_forks(size_t size)
{
	t_fork	*forks;
	size_t	i;

	i = 0;
	forks = (t_fork *)malloc(size * sizeof(t_fork));
	while (i < size)
	{
		if (pthread_mutex_init(&forks[i], NULL))
		{
			write(2, MUTEX_INIT_FAILED, ft_strlen(MUTEX_INIT_FAILED));
			return (free(forks), NULL);
		}
		i++;
	}
	return (forks);
}
