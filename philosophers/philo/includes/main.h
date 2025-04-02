/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 12:57:45 by iboubkri          #+#    #+#             */
/*   Updated: 2025/04/02 14:53:42 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdbool.h>

#define USAGE "Usage:\n\t./philo number_of_philosophers time_to_die time_to_eat \
time_to_sleep [number_of_times_each_philosopher_must_eat]\n"
#define M1 "Error:\n\tnumber of philosophers should be an unsigned integer\n"
#define M2 "Error:\n\ttime to die should be an unsigned integer\n"
#define M3 "Error:\n\ttime to eat should be an unsigned integer\n"
#define M4 "Error:\n\ttime to sleep should be an unsigned integer\n"
#define M5 "Error:\n\tnumber of times each philosopher must eat should be an \
unsigned integer\n"
#define ERR_FORKS_INIT "Error:\n\tFailed to initialize mutexes\n"
#define ERR_THREAD_JOIN "Error:\n\tFailed to join threads\n"

typedef pthread_mutex_t t_fork;

enum
{
	NB_PHILOS,
	TIME_TO_DIE,
	EAT_TIME,
	SLEEP_TIME,
	TOTAL_EAT,
};

typedef struct s_philosophers
{
	pthread_t thread;
	t_fork *left_fork;
	t_fork *right_fork;
	bool *sim_stop;
	suseconds_t eat_time;
	suseconds_t sleep_time;
	suseconds_t start_time;
	suseconds_t last_meal_time;
	int meal_eaten;
	int id;
} t_philosophers;

typedef struct s_monitor
{
	pthread_t thread;
	t_philosophers *philos;
	t_fork *forks;
	int *data;
	bool sim_stop;
} t_monitor;

int ft_strlen(char *str);
int *parse_input(char **av);
suseconds_t get_current_time(void);

t_fork *create_forks(int size);
t_philosophers *create_philosophers(t_fork *forks, int *data, bool *sim_stop);
int destroy_forks(t_fork *forks, int size);
int join_philosophers(t_philosophers *philos, int size);

void *monitor_routine(t_monitor *monitor);
void *philos_routine(t_philosophers *philo);

#endif
