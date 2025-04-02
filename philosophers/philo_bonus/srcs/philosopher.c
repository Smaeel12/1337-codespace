/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 12:19:28 by iboubkri          #+#    #+#             */
/*   Updated: 2025/04/02 16:50:19 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

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
