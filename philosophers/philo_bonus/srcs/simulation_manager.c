/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_manager.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 12:17:24 by iboubkri          #+#    #+#             */
/*   Updated: 2025/04/02 14:44:07 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

t_fork *create_forks(int size)
{
	t_fork *forks;
	int i;

	i = 0;
	forks = (t_fork *)malloc(size * sizeof(t_fork));
	while (i < size)
	{
		if (pthread_mutex_init(&forks[i], NULL))
			return (write(2, ERR_FORKS_INIT, ft_strlen(ERR_FORKS_INIT)), destroy_forks(forks, size), NULL);
		i++;
	}
	return (forks);
}

t_philosophers *create_philosophers(t_fork *forks, int *data, bool *sim_stop)
{
	t_philosophers *philos;
	int i;

	i = 0;
	philos = (t_philosophers *)malloc(data[NB_PHILOS] * sizeof(t_philosophers));
	memset(philos, 0, data[NB_PHILOS] * sizeof(t_philosophers));
	while (i < data[NB_PHILOS])
	{
		philos[i].id = i + 1;
		philos[i].right_fork = &forks[((i & 1) + i) % data[NB_PHILOS]];
		philos[i].left_fork = &forks[(!(i & 1) + i) % data[NB_PHILOS]];
		philos[i].start_time = get_current_time();
		philos[i].last_meal_time = philos[i].start_time;
		philos[i].eat_time = data[EAT_TIME] * 1000;
		philos[i].sleep_time = data[SLEEP_TIME] * 1000;
		philos[i].sim_stop = sim_stop;
		philos[i].meal_eaten = 0;
		if (pthread_create(&philos[i].thread, NULL, (void *(*)(void *))philos_routine, &philos[i]))
			return (write(2, ERR_FORKS_INIT, ft_strlen(ERR_FORKS_INIT)), destroy_forks(forks, data[NB_PHILOS]), NULL);
		i++;
	}
	return (philos);
}

int destroy_forks(t_fork *forks, int size)
{
	int i;

	i = 0;
	while (i < size)
		pthread_mutex_destroy(&forks[i++]);
	return (0);
}

int join_philosophers(t_philosophers *philos, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		if (pthread_join(philos[i].thread, NULL))
			write(2, ERR_FORKS_INIT, ft_strlen(ERR_FORKS_INIT));
		i++;
	}
	return (0);
}
