/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:22:10 by iboubkri          #+#    #+#             */
/*   Updated: 2025/04/02 16:23:40 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void *monitor(t_monitor *monitor)
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
