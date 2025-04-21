/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 16:15:50 by iboubkri          #+#    #+#             */
/*   Updated: 2025/04/21 10:40:03 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

# define USAGE_ERR \
	"Usage:\n\t./philo number_of_philosophers time_to_die \
time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n"
# define SOPEN_ERR "Error:\n\tFailed to open a semaphore\n"
# define SCLOSE_ERR "Error:\n\tFailed to close a semaphore\n"
# define MALLOC_FAILED "Error:\n\tMemory allocation failed\n"
# define TCREAT_FAILED "Error:\n\tFailed to create a thread\n"
# define TJOIN_FAILED "Error:\n\tFailed to create a thread\n"
# define SEM_FORKS "/sem_forks"
# define SEM_WRITE "/sem_write"
# define SEM_READ "/sem_read_"
# define SEM_DEATH "/sem_death"
# define MAX_NAME_LEN 20

typedef struct s_data
{
	pthread_t				kill_thread;
	size_t					nb_philos;
	suseconds_t				die_time;
	suseconds_t				eat_time;
	suseconds_t				sleep_time;
	size_t					total_eat;
	suseconds_t				start_time;
	sem_t					*forks_lock;
	sem_t					*write_lock;
	sem_t					*death_lock;
	pid_t					*pids;
}							t_data;

typedef struct s_philo
{
	size_t					id;
	size_t					nb_meals;
	suseconds_t				last_meal;
	suseconds_t				think_time;
	size_t					is_dead;
	t_data					*data;
	sem_t					*read_lock;
	char					*name;
}							t_philo;

static inline suseconds_t	getcurrenttime(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

static inline int	ft_msleep(suseconds_t msec)
{
	suseconds_t	start;

	start = getcurrenttime();
	while (getcurrenttime() - start < msec)
		usleep(500);
	return (0);
}

int							parsing_data(char **argv, t_data *data);
size_t						ft_strlen(char *str);
int							clear_data(t_data *data);
void						*kill_rotuine(t_data *data);

int							create_philosophers(t_data *data);

#endif
