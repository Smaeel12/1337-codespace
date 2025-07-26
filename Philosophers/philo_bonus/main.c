/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 16:07:47 by iboubkri          #+#    #+#             */
/*   Updated: 2025/04/18 19:10:42 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (write(2, USAGE_ERR, ft_strlen(USAGE_ERR)), 1);
	if (parsing_data(&argv[1], &data))
		return (1);
	clear_data(&data);
	data.write_lock = sem_open(SEM_WRITE, O_CREAT, 0664, 1);
	data.death_lock = sem_open(SEM_DEATH, O_CREAT, 0664, data.nb_philos);
	data.forks_lock = sem_open(SEM_FORKS, O_CREAT, 0664, data.nb_philos);
	if (data.forks_lock == SEM_FAILED || data.write_lock == SEM_FAILED
		|| data.death_lock == SEM_FAILED)
		return (write(2, SOPEN_ERR, ft_strlen(SOPEN_ERR)), 1);
	data.pids = malloc(data.nb_philos * sizeof(pid_t));
	if (!data.pids)
		return (write(2, MALLOC_FAILED, ft_strlen(MALLOC_FAILED)), 1);
	create_philosophers(&data);
	waitpid(-1, NULL, 0);
	pthread_create(&data.kill_thread, NULL, (void *(*)(void *))kill_rotuine,
		&data);
	while (waitpid(-1, NULL, 0) > 0)
		;
	sem_post(data.death_lock);
	pthread_join(data.kill_thread, NULL);
	return (clear_data(&data), 0);
}
