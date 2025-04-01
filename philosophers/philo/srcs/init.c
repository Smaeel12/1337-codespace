/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 12:17:24 by iboubkri          #+#    #+#             */
/*   Updated: 2025/04/01 15:12:08 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

pthread_mutex_t *create_forks(int size)
{
	pthread_mutex_t *forks;
	int i;

	i = 0;
	forks = (pthread_mutex_t *)malloc(size * sizeof(pthread_mutex_t));
	while (i < size)
	{
		if (pthread_mutex_init(&forks[i], NULL))
			return (write(2, ERR_FORKS_INIT, ft_strlen(ERR_FORKS_INIT)), destroy_forks(forks, size), NULL);
		i++;
	}
	return (forks);
}

t_philosophers *create_philosophers(pthread_mutex_t *forks, int *data, bool *sim_stop)
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
