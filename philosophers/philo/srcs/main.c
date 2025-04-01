/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 12:56:45 by iboubkri          #+#    #+#             */
/*   Updated: 2025/04/01 11:18:58 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int main(int ac, char **av)
{
	t_monitor monitor;

	memset(&monitor, 0, sizeof(t_monitor));
	if (ac < 5 || ac > 6)
		return (write(2, USAGE, ft_strlen(USAGE)), 1);
	monitor.data = parse_input(&av[1]);
	if (!monitor.data)
		return (1);
	monitor.forks = create_forks(monitor.data[NB_PHILOS]);
	monitor.sim_stop = 0;
	monitor.philos = NULL;
	pthread_create(&monitor.thread, NULL, (void *(*)(void *))monitor_routine, &monitor);
	monitor.philos = create_philosophers(monitor.forks, monitor.data, &monitor.sim_stop);

	join_philosophers(monitor.philos, monitor.data[NB_PHILOS]);
	pthread_join(monitor.thread, NULL);
	destroy_forks(monitor.forks, monitor.data[NB_PHILOS]);
	free(monitor.data);
	free(monitor.philos);
	free(monitor.forks);
	return (0);
}
