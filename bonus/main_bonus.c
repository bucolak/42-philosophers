/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bucolak <bucolak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 18:11:45 by bucolak           #+#    #+#             */
/*   Updated: 2025/02/26 18:50:15 by bucolak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int main(int argc, char *argv[])
{
    t_philo_data *philo;
    if(argc != 5)
        return 0;
    philo = malloc(sizeof(t_philo_data));
    philo->start_time = get_time_bonus();
    philo->time_to_die = atoll(argv[2]);
    philo->time_to_eat = atoll(argv[3]);
    philo->time_to_sleep = atoll(argv[4]);
    philo->num_of_philo=ftt_atoi(argv[1]);

    philo->philos = malloc(sizeof(t_philo) * philo->num_of_philo);
    philo->pid = malloc(sizeof(t_philo) * philo->num_of_philo);
    if(philo->num_of_philo == 1)
    {
        usleep(philo->time_to_eat*1000);
        return 0;
    }
    sem_unlink("/semaphores");
    sem_unlink("/current_time");
    sem_unlink("/dead_time");
    sem_unlink("/meal_time");
    sem_unlink("/d_time");
    sem_unlink("/death_time");
    philo->semaphores = sem_open("/semaphores", O_CREAT, 0644, philo->num_of_philo);
    philo->current_time = sem_open("/current_time", O_CREAT, 0644, 1);
    philo->dead_time = sem_open("/dead_time", O_CREAT, 0644, 1);
    philo->meal_time = sem_open("/meal_time", O_CREAT, 0644, 1);
    philo->d_time = sem_open("/d_time", O_CREAT, 0644, 1);
    philo->death_time = sem_open("/death_time", O_CREAT, 0644, 0);
    int i = 0;

    while(i < philo->num_of_philo)
    {
        philo->pid[i] = fork();
        philo->philos[i].id = i+1;
        philo->philos[i].data = philo;
        philo->philos[i].last_meal_time = get_time_bonus();
        if (philo->pid[i] == 0)
        {
            philo_bonus_routine(&philo->philos[i]);
            deta
            exit(0);
        }
        i++;
    }
    sone_died_bonus(philo);
    i = 0;
    while (i < philo->num_of_philo)
    {
        waitpid(philo->pid[i], NULL, 0);
        i++;
    }
    //sem_wait(philo->death_time);
}