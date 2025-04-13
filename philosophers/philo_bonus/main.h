/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 16:15:50 by iboubkri          #+#    #+#             */
/*   Updated: 2025/04/12 23:08:54 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
#define MAIN_H

#include <semaphore.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdbool.h>
#include <wait.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <signal.h>
#include <stdlib.h>

#define USAGE_ERR "Usage:\n\t./philo number_of_philosophers time_to_die \
time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n"

#define ERR_FORKS_INIT "Error:\n\tFailed to initialize mutexes\n"
#define ERR_THREAD_JOIN "Error:\n\tFailed to join threads\n"

suseconds_t getcurrenttime(void);
size_t ft_strlen(char *str);
size_t to_number(char *input);

#endif