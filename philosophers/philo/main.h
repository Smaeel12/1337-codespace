/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:12:19 by iboubkri          #+#    #+#             */
/*   Updated: 2025/04/20 23:57:58 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define USAGE_ERR \
	"Usage:\n\t./philo number_of_philosophers time_to_die \
time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n"
# define MUTEX_DESTROY_FAILED "Error:\n\tFailed to destroy mutexes\n"
# define MUTEX_INIT_FAILED "Error:\n\tFailed to initilaize mutexes\n"
# define THREAD_CREATE_ERR "Error:\n\tFailed to create a thread\n"
# define MALLOC_ERR "Error:\n\tFailed to allocate memory\n"

typedef pthread_mutex_t		t_fork;
typedef pthread_mutex_t		t_lock;

typedef struct s_data
{
	size_t					nb_philos;
	suseconds_t				die_time;
	suseconds_t				eat_time;
	suseconds_t				sleep_time;
	size_t					total_eat;

	suseconds_t				start_time;

	t_lock					write_lock;
	t_lock					read_lock;

	size_t					death_flag;
}							t_data;

typedef struct s_philo
{
	pthread_t				thread;
	size_t					id;
	t_data					*data;
	t_fork					*left_fork;
	t_fork					*right_fork;
	size_t					nb_meals;
	suseconds_t				last_meal;
	suseconds_t				think_time;
}							t_philo;

size_t						ft_strlen(char *str);
int							parsing_input(t_data *data, char **argv);
int							monitoring(t_philo *philos, t_data *data,
								size_t done, size_t id);
t_philo						*create_philosophers(t_fork *forks, t_data *data);
t_fork						*create_forks(size_t size);
int							join_philosophers(t_philo *philos, size_t size);
int							destroy_mutexes(t_data *data, t_fork *forks);

static inline suseconds_t	getcurrenttime(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

static inline int	ft_msleep(t_data *data, suseconds_t msec)
{
	suseconds_t	start;
	bool		is_dead;

	is_dead = false;
	start = getcurrenttime();
	while (!is_dead && getcurrenttime() - start < msec)
	{
		pthread_mutex_lock(&data->read_lock);
		is_dead = data->death_flag;
		pthread_mutex_unlock(&data->read_lock);
		usleep(500);
	}
	return (0);
}

#endif