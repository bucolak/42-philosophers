/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bucolak <bucolak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:32:47 by bucolak           #+#    #+#             */
/*   Updated: 2025/03/12 16:42:45 by bucolak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	meal_order(t_philo *philo, int left_id, int right_id)
{
	if(philo->id%2==0)
	{
		pthread_mutex_lock(&philo->data->forks[left_id]);
		pthread_mutex_lock(&philo->data->forks[right_id]);
	}
	else
	{
		pthread_mutex_lock(&philo->data->forks[right_id]);
		pthread_mutex_lock(&philo->data->forks[left_id]);
	}
	pthread_mutex_lock(&philo->data->d_lock);
	if(philo->data->someone_died)
	{
		pthread_mutex_unlock(&philo->data->d_lock);
		return ; 
	}
	pthread_mutex_unlock(&philo->data->d_lock);
	printf("%lld %d has taken a fork\n", get_time()
		- philo->data->start_time, philo->id);
	printf("%lld %d has taken a fork\n", get_time()
		- philo->data->start_time, philo->id);
	pthread_mutex_lock(&philo->data->d_lock);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->d_lock);
	printf("%lld %d is eating\n", get_time() - philo->data->start_time,
			philo->id);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->data->forks[right_id]);
	pthread_mutex_unlock(&philo->data->forks[left_id]);
}

void	sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->d_lock);
	if(philo->data->someone_died)
	{
		pthread_mutex_unlock(&philo->data->d_lock);
		return ; 
	}
	pthread_mutex_unlock(&philo->data->d_lock);
	printf("%lld %d is sleeping\n", get_time() - philo->data->start_time,
			philo->id);
	usleep(philo->data->time_to_sleep * 1000);
}

void	thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->d_lock);
	if(philo->data->someone_died)
	{
		pthread_mutex_unlock(&philo->data->d_lock);
		return ; 
	}
	pthread_mutex_unlock(&philo->data->d_lock);
	
	printf("%lld %d is thinking\n", get_time() - philo->data->start_time,
		philo->id);
}


void	*philo_routine(void *arg)
{
	t_philo	*philo;
	int		left_id;
	int		right_id;

	philo = (t_philo *)arg;
	philo->left_fork = philo->id;
	philo->right_fork = (philo->id + 1) % philo->data->num_of_philo;
	
	while (1)
	{
		pthread_mutex_lock(&philo->data->d_lock);
		if(philo->data->someone_died)
		{
			pthread_mutex_unlock(&philo->data->d_lock);
			break; 
		}
		pthread_mutex_unlock(&philo->data->d_lock);
		left_id = (philo->id - 1 + philo->data->num_of_philo)
			% philo->data->num_of_philo;
		right_id = (philo->id + 1) % philo->data->num_of_philo;
		if(philo->data->num_of_philo%2==0)
		{
			meal_order(philo, left_id, right_id);
			sleeping(philo);
			thinking(philo);
		}
		else
		{
			sleeping(philo);
			thinking(philo);
			meal_order(philo, left_id, right_id);
		}
	}
	return (NULL);
}
