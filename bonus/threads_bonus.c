/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bucolak <bucolak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 18:11:38 by bucolak           #+#    #+#             */
/*   Updated: 2025/02/24 14:46:45 by bucolak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void *philo_bonus_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    while(42)
    {
        printf("%lld %d is thinking\n",get_time_bonus(), philo->id);
        
        sem_wait(philo->data->semaphores);
        printf("%lld %d has taken a fork\n",get_time_bonus(), philo->id);

        sem_wait(philo->data->semaphores);
        printf("%lld %d has taken a fork\n",get_time_bonus(), philo->id);

        long long curr= get_time_bonus();
        philo->last_meal_time = curr;
        
        printf("%lld %d is eating\n",get_time_bonus(), philo->id);
        usleep(philo->data->time_to_eat*1000);
 
        sem_post(philo->data->semaphores);  
        sem_post(philo->data->semaphores);

        printf("%lld %d is sleeping\n",get_time_bonus(), philo->id);
        usleep(philo->data->time_to_sleep*1000);
    }
    return NULL;       
}

void *sone_died_bonus(t_philo_data *philo)
{
	int i;
    while(42)
    {
        i = 0;
        while (i < philo->num_of_philo)
        {
		    
			if((get_time_bonus() - philo->philos[i].last_meal_time) >= philo->time_to_die)
			{
                
				printf("%lld %d died\n", get_time_bonus(), i+1);
                sem_post(philo->death_time);
                for(int i = 0;i < philo->num_of_philo;i++)
                    kill(philo->pid[i], SIGTERM);
                exit(0);
			}

			i++;
    	}
        usleep(1000);
    }
    return NULL;
}