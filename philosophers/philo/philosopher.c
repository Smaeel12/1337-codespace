/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 01:22:30 by iboubkri          #+#    #+#             */
/*   Updated: 2025/04/11 14:52:28 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	display_message(t_philo *philo, char *action)
{
	bool	stop_sim;

	pthread_mutex_lock(philo->read_lock);
	stop_sim = philo->is_dead;
	pthread_mutex_unlock(philo->read_lock);
	if (stop_sim == false)
	{
		pthread_mutex_lock(philo->write_lock);
		printf("%li %li %s\n", (getcurrenttime() - philo->start_time),
			philo->id, action);
		pthread_mutex_unlock(philo->write_lock);
	}
	return (!stop_sim);
}

static void	*thread_routine(t_philo *philo)
{
	while (display_message(philo, "is thinking"))
	{
		usleep((philo->id & 1));
		pthread_mutex_lock(philo->left_fork);
		display_message(philo, "has taken a fork");
		if (philo->left_fork == philo->right_fork)
			return (NULL);
		pthread_mutex_lock(philo->right_fork);
		display_message(philo, "has taken a fork");
		{
			pthread_mutex_lock(philo->read_lock);
			philo->nb_meals += 1;
			philo->last_meal = getcurrenttime();
			pthread_mutex_unlock(philo->read_lock);
			display_message(philo, "is eating");
			usleep(philo->data[EAT_TIME] * 1000);
		}
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		display_message(philo, "is sleeping");
		usleep(philo->data[SLEEP_TIME] * 1000);
	}
	return (NULL);
}

int	monitoring(t_philo *philos, t_data *data)
{
	size_t	philos_done;
	size_t	i;

	while (1)
	{
		i = 0;
		philos_done = 0;
		while (i < data[NB_PHILOS])
		{
			if (getcurrenttime()
				- philos[i].last_meal >= (suseconds_t)data[TIME_TO_DIE])
			{
				display_message(&philos[i], "died");
				return (0);
			}
			pthread_mutex_lock(philos->read_lock);
			philos_done += philos[i].nb_meals >= data[TOTAL_EAT];
			pthread_mutex_unlock(philos->read_lock);
			i++;
		}
		if (data[TOTAL_EAT] && philos_done >= data[NB_PHILOS])
			return (0);
	}
	return (0);
}

t_philo	*create_philosophers(t_fork *forks, t_data *data, t_lock *locks)
{
	t_philo		*philos;
	suseconds_t	start_time;
	size_t		i;

	i = 0;
	start_time = getcurrenttime();
	philos = (t_philo *)malloc(data[NB_PHILOS] * sizeof(t_philo));
	while (philos && i < data[NB_PHILOS])
	{
		philos[i].id = i + 1;
		philos[i].left_fork = &forks[(!(i & 1) + i) % data[NB_PHILOS]];
		philos[i].right_fork = &forks[((i & 1) + i) % data[NB_PHILOS]];
		philos[i].last_meal = getcurrenttime();
		philos[i].nb_meals = 0;
		philos[i].read_lock = &locks[READ];
		philos[i].write_lock = &locks[WRITE];
		philos[i].start_time = start_time;
		philos[i].is_dead = false;
		philos[i].data = data;
		if (pthread_create(&philos[i].thread, NULL,
				(void *(*)(void *))thread_routine, &philos[i]))
			return (free(philos), NULL);
		i++;
	}
	return (philos);
}

t_fork	*create_forks(int size)
{
	t_fork	*forks;
	int		i;

	i = 0;
	forks = (t_fork *)malloc(size * sizeof(t_fork));
	while (i < size)
	{
		if (pthread_mutex_init(&forks[i], NULL))
			return (free(forks), write(2, "ERR_FORKS_INIT",
					ft_strlen("ERR_FORKS_INIT")), NULL);
		i++;
	}
	return (forks);
}
