/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:12:19 by iboubkri          #+#    #+#             */
/*   Updated: 2025/04/11 14:51:00 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define USAGE_ERR \
	"Usage:\n\t./philo number_of_philosophers time_to_die time_to_eat \
time_to_sleep [number_of_times_each_philosopher_must_eat]\n"
# define MUTEX_DESTROY_FAILED "Error:\n\tFailed to destroy mutexes\n"
# define MUTEX_INIT_FAILED "Error:\n\tFailed to initilaize mutexes\n"
# define THREAD_CREATE_ERR "Error:\n\tFailed to create a thread\n"

# define READ 0
# define WRITE 1

typedef size_t			t_data;
typedef pthread_mutex_t	t_fork;
typedef pthread_mutex_t	t_lock;

typedef struct s_philo
{
	pthread_t			thread;
	size_t				id;
	t_data				*data;
	t_fork				*left_fork;
	t_fork				*right_fork;
	t_lock				*write_lock;
	t_lock				*read_lock;
	size_t				nb_meals;
	suseconds_t			last_meal;
	suseconds_t			start_time;
	bool				is_dead;
}						t_philo;

enum
{
	NB_PHILOS,
	TIME_TO_DIE,
	EAT_TIME,
	SLEEP_TIME,
	TOTAL_EAT,
};

size_t					ft_strlen(char *str);
t_data					*parsing_input(char **argv);
suseconds_t				getcurrenttime(void);

t_fork					*create_forks(int size);
t_philo					*create_philosophers(t_fork *forks, t_data *data,
							t_lock *locks);
int						monitoring(t_philo *philos, t_data *data);

#endif