/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:22:53 by iboubkri          #+#    #+#             */
/*   Updated: 2025/04/20 17:46:02 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philos;
	t_fork	*forks;

	philos = NULL;
	forks = NULL;
	if (argc < 5 || argc > 6)
		return (write(2, USAGE_ERR, ft_strlen(USAGE_ERR)), 1);
	if (parsing_input(&data, &argv[1]))
		return (1);
	if (pthread_mutex_init(&data.read_lock, NULL)
		|| pthread_mutex_init(&data.write_lock, NULL))
		return (1);
	forks = create_forks(data.nb_philos);
	if (!forks)
		return (1);
	philos = create_philosophers(forks, &data);
	if (!philos)
		return (1);
	monitoring(philos, &data, 0, 0);
	join_philosophers(philos, data.nb_philos);
	destroy_mutexes(&data, forks);
	return (0);
}
