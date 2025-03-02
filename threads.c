/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bucolak <bucolak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:32:47 by bucolak           #+#    #+#             */
/*   Updated: 2025/03/02 18:44:25 by bucolak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	meal_order(t_philo *philo, int left_id, int right_id)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->data->forks[left_id]);
		printf("%lld %d has taken a fork\n", get_time(), philo->id);
		pthread_mutex_lock(&philo->data->forks[right_id]);
		printf("%lld %d has taken a fork\n", get_time(), philo->id);
		pthread_mutex_lock(&philo->data->t_lock);
		philo->data->t = 1;
		pthread_mutex_unlock(&philo->data->t_lock);
	}
	else
	{
		pthread_mutex_lock(&philo->data->forks[right_id]);
		printf("%lld %d has taken a fork\n", get_time(), philo->id);
		pthread_mutex_lock(&philo->data->forks[left_id]);
		printf("%lld %d has taken a fork\n", get_time(), philo->id);
		pthread_mutex_lock(&philo->data->t_lock);
		philo->data->t = 0;
		pthread_mutex_unlock(&philo->data->t_lock);
	}
}

void	meal_order2(t_philo *philo)
{
	while ((philo->id % 2 == 0 && philo->data->t != 0) || (philo->id % 2 != 0
			&& philo->data->t != 1))
	{
		pthread_mutex_unlock(&philo->data->m_lock);
		usleep(1000);
		pthread_mutex_lock(&philo->data->m_lock);
	}
	if (philo->data->num_of_philo == 1)
	{
        printf("%lld %d died\n", get_time(), philo->id);
		usleep(philo->data->time_to_die * 1000);
		free_full(philo->data);
		exit(0);
	}
}

void last_routine(t_philo *philo,int left_id, int right_id)
{
    	pthread_mutex_unlock(&philo->data->forks[right_id]);
		pthread_mutex_unlock(&philo->data->forks[left_id]);
		printf("%lld %d is sleeping\n", get_time(), philo->id);
		usleep(philo->data->time_to_sleep * 1000);
}

void	*philo_routine_2(void *arg)
{
	t_philo		*philo;
	int			left_id;
	int			right_id;

	philo = (t_philo *)arg;
	philo->left_fork = philo->id;
	philo->right_fork = (philo->id + 1) % philo->data->num_of_philo;
	while (1)
	{
		left_id = (philo->id - 1 + philo->data->num_of_philo)
			% philo->data->num_of_philo;
		right_id = (philo->id + 1) % philo->data->num_of_philo;
		pthread_mutex_lock(&philo->data->m_lock);
		meal_order2(philo);
		pthread_mutex_unlock(&philo->data->m_lock);
		printf("%lld %d is thinking\n", get_time(), philo->id);
		meal_order(philo, left_id, right_id);
		pthread_mutex_lock(&philo->data->meal_lock);
		philo->last_meal_time = get_time();
		pthread_mutex_unlock(&philo->data->meal_lock);
		printf("%lld %d is eating\n", get_time(), philo->id);
		usleep(philo->data->time_to_eat * 1000);
        last_routine(philo, left_id, right_id);
	}
	free_full(philo->data);
	return (NULL);
}

// left_id = philo->left_fork;
// 	right_id = philo->right_fork;