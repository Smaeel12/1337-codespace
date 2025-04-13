/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:22:53 by iboubkri          #+#    #+#             */
/*   Updated: 2025/04/11 14:56:46 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	main(int argc, char **argv)
{
	t_data	*data;
	t_philo	*philos;
	t_fork	*forks;
	t_lock	lock[2];

	if (argc < 5 || argc > 6)
		return (write(2, USAGE_ERR, ft_strlen(USAGE_ERR)), 1);
	data = parsing_input(&argv[1]);
	if (!data)
		return (1);
	forks = create_forks(data[NB_PHILOS]);
	if (!forks)
		return (free(data), 1);
	if (pthread_mutex_init(&lock[READ], NULL)
		|| pthread_mutex_init(&lock[WRITE], NULL))
		return (free(data), free(forks), write(2, MUTEX_INIT_FAILED,
				ft_strlen(MUTEX_INIT_FAILED)), 1);
	philos = create_philosophers(forks, data, lock);
	if (!philos)
		return (free(data), free(forks), write(2, THREAD_CREATE_ERR,
				ft_strlen(THREAD_CREATE_ERR)), 1);
	monitoring(philos, data);
	return (free(forks), free(philos), free(data), 0);
}
