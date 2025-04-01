/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 12:19:28 by iboubkri          #+#    #+#             */
/*   Updated: 2025/04/01 16:17:23 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int display_message(char *action, int id, suseconds_t start_time, int sim_stop)
{
	if (sim_stop)
		return (1);
	printf("%li %i %s\n", (get_current_time() - start_time), id, action);
	return (0);
}

void *monitor_routine(t_monitor *monitor)
{
	int philos_done;
	int i;

	while (!monitor->sim_stop)
	{
		i = 0;
		philos_done = 0;
		while (!monitor->sim_stop && monitor->philos && i < monitor->data[NB_PHILOS])
		{
			if (get_current_time() - monitor->philos[i].last_meal_time >= monitor->data[TIME_TO_DIE])
			{
				display_message("died", monitor->philos[i].id, monitor->philos[i].start_time, 0);
				monitor->sim_stop = 1;
			}
			philos_done += monitor->philos[i].meal_eaten >= monitor->data[TOTAL_EAT];
			i++;
		}
		if (monitor->data[TOTAL_EAT] && philos_done >= monitor->data[NB_PHILOS])
			monitor->sim_stop = 1;
	}
	return NULL;
}

void *philos_routine(t_philosophers *philo)
{
	while (!*(philo->sim_stop))
	{
		pthread_mutex_lock(philo->left_fork);
		display_message("takes a fork", philo->id, philo->start_time, *philo->sim_stop);
		if (philo->left_fork == philo->right_fork)
			break;
		pthread_mutex_lock(philo->right_fork);
		display_message("takes a fork", philo->id, philo->start_time, *philo->sim_stop);
		{
			philo->meal_eaten += 1;
			philo->last_meal_time = get_current_time();
			display_message("is eating", philo->id, philo->start_time, *philo->sim_stop);
			usleep(philo->eat_time);
		}
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		display_message("is sleeping", philo->id, philo->start_time, *philo->sim_stop);
		usleep(philo->sleep_time);
		display_message("is thinking", philo->id, philo->start_time, *philo->sim_stop);
	}
	return NULL;
}
