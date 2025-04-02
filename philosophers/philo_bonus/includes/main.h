/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 12:57:45 by iboubkri          #+#    #+#             */
/*   Updated: 2025/04/02 16:57:02 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
#define MAIN_H

// new update
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
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

typedef sem_t t_forks;

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
	pid_t pid;
	// bool *sim_stop;
	// suseconds_t last_meal_time;
	int meal_eaten;
	// int id;
} t_philosophers;

typedef struct s_monitor
{
	t_philosophers *philos;
	t_forks *forks;
	int *data;
	bool sim_stop;
} t_monitor;

int ft_strlen(char *str);
int *parse_input(char **av);
suseconds_t get_current_time(void);

#endif
