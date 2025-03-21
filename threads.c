/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bucolak <bucolak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:32:47 by bucolak           #+#    #+#             */
/*   Updated: 2025/03/21 16:32:57 by bucolak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	meal_order(t_philo *philo, int left_id, int right_id)
{
	pthread_mutex_lock(&philo->data->forks[left_id]);
	if (philo->data->num_of_philo == 1)
	{
		printf("%lld %d has taken a fork\n", get_time()
			- philo->data->start_time, philo->id);
		pthread_mutex_unlock(&philo->data->forks[left_id]);
		return ;
	}
	pthread_mutex_lock(&philo->data->forks[right_id]);
	printf("%lld %d has taken a fork\n", get_time() - philo->data->start_time,
		philo->id);
	printf("%lld %d has taken a fork\n", get_time() - philo->data->start_time,
		philo->id);
	dead_cont_2(philo, left_id, right_id);
	pthread_mutex_lock(&philo->data->d_lock);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->d_lock);
	printf("%lld %d is eating\n", get_time() - philo->data->start_time,
		philo->id);
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->data->forks[right_id]);
	pthread_mutex_unlock(&philo->data->forks[left_id]);
}

void	sleeping(t_philo *philo)
{
	if (cont_dead(philo) == 1)
		return ;
	printf("%lld %d is sleeping\n", get_time() - philo->data->start_time,
		philo->id);
	ft_usleep(philo->data->time_to_sleep);
}

void	thinking(t_philo *philo)
{
	if (cont_dead(philo) == 1)
		return ;
	printf("%lld %d is thinking\n", get_time() - philo->data->start_time,
		philo->id);
}

void	routine(t_philo *philo, int left_id, int right_id)
{
	if (philo->data->num_of_philo % 2 == 0)
	{
		if (philo->id % 2 == 0)
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
	else
	{
		meal_order(philo, left_id, right_id);
		if (philo->data->num_of_philo == 1)
			return ;
		sleeping(philo);
		thinking(philo);
	}
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	int		left_id;
	int		right_id;

	philo = (t_philo *)arg;
	if (philo->data->num_of_philo % 2 == 1 && philo->data->num_of_philo != 1)
	{
		if (philo->id % 2 == 1)
			ft_usleep(100);
	}
	while (cont_dead(philo) == 0)
	{
		if (cont_dead(philo))
			return (NULL);
		left_id = philo->id - 1;
		if (philo->id == 1)
			right_id = philo->data->num_of_philo - 1;
		else
			right_id = philo->id - 2;
		routine(philo, left_id, right_id);
		if (philo->data->num_of_philo == 1)
			return (NULL);
	}
	return (NULL);
}
