/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 16:07:47 by iboubkri          #+#    #+#             */
/*   Updated: 2025/04/13 01:45:13 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

#define SEM_FORKS "/sem_forks"
#define SEM_WRITE "/sem_write"
#define SEM_READ "/sem_read"
#define SEM_DEATH "/sem_death"

typedef struct s_data
{
    size_t nb_philos;
    suseconds_t die_time;
    suseconds_t eat_time;
    suseconds_t sleep_time;
    suseconds_t start_time;
    size_t total_eat;
} t_data;

typedef struct s_locks
{
    sem_t *forks_lock;
    sem_t *write_lock;
    sem_t *death_lock;
} t_locks;

typedef struct s_philo
{
    pthread_t thread;
    size_t id;
    size_t nb_meals;
    suseconds_t last_meal;
    sem_t *read_lock;
    t_locks *locks;
    t_data *data;
} t_philo;

int ft_msleep(suseconds_t msec)
{
    suseconds_t start;
    suseconds_t current;
    suseconds_t elapsed;

    start = getcurrenttime();
    while (1)
    {
        current = getcurrenttime();
        elapsed = current - start;
        if (elapsed >= msec)
            break;

        // Sleep for shorter intervals to maintain precision
        // Calculate remaining time and sleep for a fraction of it
        usleep((msec - elapsed) / 2);
    }
    return (0);
}

static int display_message(t_philo *philo, char *action)
{
    sem_wait(philo->locks->write_lock);
    printf("%li %li %s\n", (getcurrenttime() - philo->data->start_time), philo->id, action);
    sem_post(philo->locks->write_lock);
    return (0);
}

void *thread_routine(t_philo *philo)
{
    while (1)
    {
        display_message(philo, "is thinking");
        sem_wait(philo->locks->forks_lock);
        sem_wait(philo->locks->forks_lock);
        {
            display_message(philo, "has taken a fork");
            display_message(philo, "has taken a fork");
            sem_wait(philo->read_lock);
            philo->nb_meals += 1;
            philo->last_meal = getcurrenttime();
            printf("%li %li\n", philo->id, getcurrenttime() - philo->last_meal);
            sem_post(philo->read_lock);
            display_message(philo, "is eating");
            ft_msleep(philo->data->eat_time);
        }
        sem_post(philo->locks->forks_lock);
        sem_post(philo->locks->forks_lock);
        display_message(philo, "is sleeping");
        ft_msleep(philo->data->sleep_time);
    }
    return (NULL);
}

int monitoring(t_philo *philo, t_data *data)
{
    size_t stop;

    stop = 0;
    while (!stop)
    {
        usleep(philo->data->eat_time / 2);
        sem_wait(philo->read_lock);
        stop = ((data->total_eat && philo->nb_meals >= data->total_eat) << 0) |
               ((getcurrenttime() - philo->last_meal >= data->die_time) << 1);
        sem_post(philo->read_lock);
        if (stop == 1 << 1)
        {
            printf("%li %li\n", philo->id, getcurrenttime() - philo->last_meal);
            display_message(philo, "died");
        }
    }
    sem_wait(philo->locks->write_lock);
    sem_post(philo->locks->death_lock);
    return (0);
}

int stop_simulation(pid_t *pid, t_data *data)
{
    size_t i;

    i = 0;
    while (i < data->nb_philos)
    {
        kill(pid[i], SIGKILL);
        i++;
    }
    return (0);
}

int create_philosophers(t_locks *locks, t_data *data)
{
    t_philo philo;
    pid_t pid[data->nb_philos];
    size_t i;

    i = 0;
    data->start_time = getcurrenttime();
    while (i < data->nb_philos)
    {
        pid[i] = fork();
        if (pid[i] < 0)
            return (1);
        if (pid[i] == 0)
        {
            sem_unlink(SEM_READ);
            philo.read_lock = sem_open(SEM_READ, O_CREAT, 0664, 1);
            philo.id = i + 1;
            philo.nb_meals = 0;
            philo.locks = locks;
            philo.data = data;
            philo.last_meal = data->start_time;
            pthread_create(&philo.thread, NULL, (void *(*)(void *))thread_routine, &philo);
            monitoring(&philo, data);
            pthread_join(philo.thread, NULL);
            sem_close(philo.read_lock);
            sem_unlink(SEM_READ);
            exit(0);
        }
        i++;
    }
    sem_wait(locks->death_lock);
    stop_simulation(pid, data);
    return (0);
}

int open_semaphores(t_locks *locks, t_data *data)
{
    sem_unlink(SEM_FORKS);
    sem_unlink(SEM_WRITE);
    sem_unlink(SEM_DEATH);
    locks->forks_lock = sem_open(SEM_FORKS, O_CREAT, 0664, data->nb_philos);
    locks->write_lock = sem_open(SEM_WRITE, O_CREAT, 0664, 1);
    locks->death_lock = sem_open(SEM_DEATH, O_CREAT, 0664, 0);
    if (locks->forks_lock == SEM_FAILED || locks->write_lock == SEM_FAILED || locks->death_lock == SEM_FAILED)
        return (1);
    return (0);
}

int close_semaphores(t_locks *locks)
{
    sem_close(locks->forks_lock);
    sem_unlink(SEM_FORKS);
    sem_close(locks->write_lock);
    sem_unlink(SEM_WRITE);
    sem_close(locks->death_lock);
    sem_unlink(SEM_DEATH);
    return (0);
}

int parsing_data(t_data *data, char **argv)
{
    size_t error;
    char **message;

    message = (char *[]){
        "Error:\n\tnumber of times each philosopher must eat should be bigger \
than zero\n",
        "Error:\n\tnumber of philosophers should be bigger than zero\n",
        "Error:\n\ttime to die should be bigger than zero\n",
        "Error:\n\ttime to eat should be bigger than zero\n",
        "Error:\n\ttime to sleep should be bigger than zero\n",
    };
    data->nb_philos = to_number(argv[0]);
    data->die_time = to_number(argv[1]);
    data->eat_time = to_number(argv[2]);
    data->sleep_time = to_number(argv[3]);
    data->total_eat = to_number(argv[4]);
    error = (!data->nb_philos * 1) + (!data->die_time * 2) +
            (!data->eat_time * 3) + (!data->sleep_time * 4) +
            ((argv[4] && !data->total_eat) * 5);
    if (error)
        return (write(2, message[error % 5], ft_strlen(message[error % 5])), 1);
    return (0);
}

int main(int argc, char **argv)
{
    t_data data;
    t_locks locks;

    if (argc < 5 || argc > 6)
        return (write(2, USAGE_ERR, ft_strlen(USAGE_ERR)), 1);
    if (parsing_data(&data, &argv[1]) || open_semaphores(&locks, &data) || create_philosophers(&locks, &data) || close_semaphores(&locks))
        return (1);
    return (0);
}