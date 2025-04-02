/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 12:56:45 by iboubkri          #+#    #+#             */
/*   Updated: 2025/04/02 17:19:13 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int display_message(char *action, int id, suseconds_t start_time)
{
	printf("%i %i %s\n", (get_current_time() - start_time), id, action);
	return (0);
}

int main(int ac, char **av)
{
	t_philosophers *philos;
	t_forks *forks;
	int *data;
	suseconds_t start_time;

	if (ac < 5 || ac > 6)
		return (write(2, USAGE, ft_strlen(USAGE)), 1);
	data = parse_input(&av[1]);
	if (!data)
		return (1);
	philos = (t_philosophers *)malloc(data[NB_PHILOS] * sizeof(t_philosophers));
	memset(philos, 0, data[NB_PHILOS] * sizeof(t_philosophers));
	forks = sem_open("forks", O_CREAT, 0664, 1);
	start_time = get_current_time();
	for (int i = 0; i < data[NB_PHILOS]; i++)
	{
		philos[i].pid = fork();
		if (philos[i].pid < 0)
			return (0);
		if (philos[i].pid == 0)
		{
			while (1)
			{
				sem_wait(forks);
				display_message("takes a fork", i + i, start_time);
				display_message("takes a fork", i + i, start_time);
				display_message("is eating", i + i, start_time);
				philos[i].meal_eaten += 1;
				if (philos[i].meal_eaten >= data[TOTAL_EAT])
					usleep(data[EAT_TIME]);
				sem_post(forks);
				display_message("is sleeping", i + i, start_time);
				usleep(data[SLEEP_TIME]);
				display_message("is thinking", i + i, start_time);
			}
			exit(0);
		}
	}
	for (int i = 0; i < data[NB_PHILOS]; i++)
	{
		waitpid(-1, NULL, 0);
	}

	sem_close(forks);
	sem_unlink("forks");

	free(data);
	free(philos);
	return (0);
}
