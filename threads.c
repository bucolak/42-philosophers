/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buket <buket@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:32:47 by bucolak           #+#    #+#             */
/*   Updated: 2025/03/16 15:34:04 by buket            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int cont_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->d_lock);
	if(philo->data->someone_died)
	{
		pthread_mutex_unlock(&philo->data->d_lock);
		return 1;
	}
	pthread_mutex_unlock(&philo->data->d_lock);
	return 0;
}

void	meal_order(t_philo *philo, int left_id, int right_id)
{
	if(cont_dead(philo)==1) return ;
	pthread_mutex_lock(&philo->data->forks[left_id]);
	pthread_mutex_lock(&philo->data->forks[right_id]);
	printf("%lld %d has taken a fork\n", get_time()
		- philo->data->start_time, philo->id);
	printf("%lld %d has taken a fork\n", get_time()
		- philo->data->start_time, philo->id);
	if(cont_dead(philo)==1) 
	{
		pthread_mutex_unlock(&philo->data->forks[right_id]);
		pthread_mutex_unlock(&philo->data->forks[left_id]);
		return ;
	}
	pthread_mutex_lock(&philo->data->d_lock);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->d_lock);
	printf("%lld %d is eating\n", get_time() - philo->data->start_time,
			philo->id);
	if(cont_dead(philo)==1)
		return ;
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->data->forks[right_id]);
	pthread_mutex_unlock(&philo->data->forks[left_id]);
}

void	sleeping(t_philo *philo)
{
	if(cont_dead(philo)==1) return ;
	printf("%lld %d is sleeping\n", get_time() - philo->data->start_time,
			philo->id);
	ft_usleep(philo->data->time_to_sleep);
}

void	thinking(t_philo *philo)
{
	if(cont_dead(philo)==1) return ;
	printf("%lld %d is thinking\n", get_time() - philo->data->start_time,
		philo->id);
}


void	*philo_routine(void *arg)
{
	t_philo	*philo;
	int		left_id;
	int		right_id;

	philo = (t_philo *)arg;
	
	while (cont_dead(philo)==0)
	{
		if (cont_dead(philo))
			return NULL;
		left_id = (philo->id - 1 + philo->data->num_of_philo)
			% philo->data->num_of_philo;
		right_id = (philo->id + 1) % philo->data->num_of_philo;
		meal_order(philo,left_id,right_id);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
