/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bucolak <bucolak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 18:09:12 by bucolak           #+#    #+#             */
/*   Updated: 2025/02/24 14:10:09 by bucolak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <string.h>
#include <semaphore.h>
#include <fcntl.h> 
#include <sys/wait.h>
#include <signal.h>
typedef struct s_philo
{
    int is_eating;
    int is_sleeping;
    int id;
    int meals_eaten;
    long long last_meal_time;
    struct s_philo_data *data;
    char *status;
    int count;
}   t_philo;

typedef struct s_philo_data
{
    int num_of_philo;
    t_philo *philos;
    int time_to_think;
    int time_to_eat;
    int time_to_die;
    int time_to_sleep;
    int must_eat_c;
    long long start_time;
    sem_t *semaphores;
    sem_t *current_time;
    sem_t *dead_time;
    sem_t *meal_time;
    sem_t *d_time;
    sem_t *death_time;
    int *pid;
}   t_philo_data;

long long get_time_bonus();
void *philo_bonus_routine(void *arg);
int	ftt_atoi(const char *str);
void *sone_died_bonus(t_philo_data *philo);

#endif