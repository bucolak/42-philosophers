/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bucolak <bucolak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:25:00 by bucolak           #+#    #+#             */
/*   Updated: 2025/03/21 16:33:07 by bucolak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h" 

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < milliseconds)
		usleep(50);
	return (0);
}

void	free_full(t_philo_data *philo)
{
	int	i;

	i = 0;
	while (i < philo->num_of_philo)
	{
		pthread_mutex_destroy(&philo->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&philo->d_lock);
	free(philo->philos);
	free(philo->forks);
	free(philo);
}

void	dead_cont_2(t_philo *philo, int left_id, int right_id)
{
	if (cont_dead(philo) == 1)
	{
		pthread_mutex_unlock(&philo->data->forks[right_id]);
		pthread_mutex_unlock(&philo->data->forks[left_id]);
		return ;
	}
}

int	ft_atoi(const char *str)
{
	int	s;
	int	k;
	int	i;

	s = 1;
	k = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
	{
		i++;
	}
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
		{
			s = -1;
		}
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		k = k * 10 + (str[i] - '0');
		i++;
	}
	return (k * s);
}

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
