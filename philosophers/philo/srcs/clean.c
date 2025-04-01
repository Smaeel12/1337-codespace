/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 12:17:59 by iboubkri          #+#    #+#             */
/*   Updated: 2025/03/31 16:15:04 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int destroy_forks(pthread_mutex_t *forks, int size)
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
