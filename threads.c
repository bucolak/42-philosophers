/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buket <buket@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:32:47 by bucolak           #+#    #+#             */
/*   Updated: 2025/03/15 14:07:06 by buket            ###   ########.fr       */
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
	if((philo->id==1 || philo->id==philo->data->num_of_philo) && philo->data->num_of_philo%2==1)
	{
		while (1)
		{
			if(cont_dead(philo)==1) return ;
			pthread_mutex_lock(&philo->data->d2_lock);
			if ((philo->id == 1 && philo->data->two == 1) ||
				(philo->id == philo->data->num_of_philo && philo->data->two == 0))
			{
				pthread_mutex_unlock(&philo->data->d2_lock);
				break;
			}
		pthread_mutex_unlock(&philo->data->d2_lock);
		ft_usleep(500);
		}
	}
	if(cont_dead(philo)==1) return ;
	pthread_mutex_lock(&philo->data->forks[right_id]);
	pthread_mutex_lock(&philo->data->forks[left_id]);
	printf("%lld %d has taken a fork\n", get_time()
		- philo->data->start_time, philo->id);
	printf("%lld %d has taken a fork\n", get_time()
		- philo->data->start_time, philo->id);
	if((philo->id==1 || philo->id==philo->data->num_of_philo)  && philo->data->num_of_philo%2==1)
	{
		pthread_mutex_lock(&philo->data->d2_lock);
		if(philo->id==1)
			philo->data->two=1;
		else if(philo->id==philo->data->num_of_philo)
			philo->data->two=0;
		pthread_mutex_unlock(&philo->data->d2_lock);
	}
	if(cont_dead(philo)==1) return ;
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
	if((philo->id==1 || philo->id==philo->data->num_of_philo) && philo->data->num_of_philo%2==1)
	{
		pthread_mutex_lock(&philo->data->d2_lock);
		if(philo->id==1)
			philo->data->two=0;
		else if(philo->id==philo->data->num_of_philo)
			philo->data->two=1;
		pthread_mutex_unlock(&philo->data->d2_lock);
	}
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
		if(philo->id%2==0)
		{
			sleeping(philo);
			if (cont_dead(philo)) return NULL;
			thinking(philo);
			if (cont_dead(philo)) return NULL;
			meal_order(philo, left_id, right_id);
			if (cont_dead(philo)) return NULL;
		}
		else
		{
			meal_order(philo, left_id, right_id);
			if (cont_dead(philo)) return NULL;
			sleeping(philo);
			if (cont_dead(philo)) return NULL;
			thinking(philo);
		}
	}
	return (NULL);
}
