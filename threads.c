/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buket <buket@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:32:47 by bucolak           #+#    #+#             */
/*   Updated: 2025/03/07 00:22:18 by buket            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	meal_order_odd(t_philo *philo, int left_id, int right_id)
{
			while(philo->data->fork[right_id].b!=0 && philo->data->fork[left_id].b!=0)
				usleep(100);
			pthread_mutex_lock(&philo->data->forks[left_id]);
			printf("%lld %d has taken a fork\n", get_time()
				- philo->data->start_time, philo->id);
			pthread_mutex_lock(&philo->data->forks[right_id]);
			printf("%lld %d has taken a fork\n", get_time()
				- philo->data->start_time, philo->id);
			pthread_mutex_lock(&philo->data->d2_lock);
			philo->data->fork[left_id].b=1;
			philo->data->fork[right_id].b=1;
			pthread_mutex_unlock(&philo->data->d2_lock);
}

// void	meal_order_even(t_philo *philo, int left_id, int right_id)
// {		
// 		while(philo->data->two!=0)
// 			usleep(100);
// 			pthread_mutex_lock(&philo->data->forks[right_id]);
// 		printf("%lld %d has taken a fork\n", get_time()
// 				- philo->data->start_time, philo->id);
// 		pthread_mutex_lock(&philo->data->forks[left_id]);
// 		printf("%lld %d has taken a fork\n", get_time()
// 				- philo->data->start_time, philo->id);
// 		pthread_mutex_lock(&philo->data->d4_lock);
// 		philo->data->two=1;
// 		pthread_mutex_lock(&philo->data->d4_lock);
// }

// 1 uyuyo
void	last_routine(t_philo *philo, int left_id, int right_id)
{
	if (philo->data->someone_died == 1)
		return ;
	pthread_mutex_lock(&philo->data->d2_lock);
philo->data->fork[left_id].b = 0;
philo->data->fork[right_id].b = 0;
pthread_mutex_unlock(&philo->data->d2_lock);
pthread_mutex_unlock(&philo->data->forks[right_id]);
pthread_mutex_unlock(&philo->data->forks[left_id]);
// pthread_mutex_lock(&philo->data->d4_lock);
// 		philo->data->two=0;
// 		pthread_mutex_lock(&philo->data->d4_lock);
	printf("%lld %d is sleeping\n", get_time() - philo->data->start_time,
			philo->id);
	usleep(philo->data->time_to_sleep * 1000);
}

void	*philo_routine_2(void *arg)
{
	t_philo	*philo;
	int		left_id;
	int		right_id;

	philo = (t_philo *)arg;
	philo->left_fork = philo->id;
	philo->right_fork = (philo->id + 1) % philo->data->num_of_philo;
	while (philo->data->someone_died != 1)
	{
		left_id = (philo->id - 1 + philo->data->num_of_philo)
			% philo->data->num_of_philo;
		right_id = (philo->id + 1) % philo->data->num_of_philo;
		if (philo->data->num_of_philo == 1)
		{
			printf("%lld %d died\n", get_time() - philo->data->start_time,
				philo->id);
			usleep(philo->data->time_to_die * 1000);
			free_full(philo->data);
			exit(0);
		}
		printf("%lld %d is thinking\n", get_time() - philo->data->start_time,
				philo->id);
		meal_order_odd(philo, left_id, right_id);
		pthread_mutex_lock(&philo->data->meal_lock);
		philo->last_meal_time = get_time();
		philo->meals_eaten++;
		pthread_mutex_unlock(&philo->data->meal_lock);
		printf("%lld %d is eating\n", get_time() - philo->data->start_time,
				philo->id);
		usleep(philo->data->time_to_eat * 1000);
		last_routine(philo, left_id, right_id);
	}
	return (NULL);
}
