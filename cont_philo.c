/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cont_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bucolak <bucolak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:50:43 by bucolak           #+#    #+#             */
/*   Updated: 2025/03/09 20:30:32 by bucolak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_philo(t_philo_data *philo)
{
	int	i;

	i = 0;
	while (i < philo->num_of_philo)
	{
		philo->philos[i].id = i + 1;
		philo->fork[i].id=i+1;
		philo->philos[i].last_meal_time = philo->start_time;
		philo->philos[i].meals_eaten = 0;
		philo->philos[i].data = philo;
		philo->two = 0;
		pthread_create(&philo->philos[i].thread, NULL, philo_routine,
				&philo->philos[i]);
		i++;
	}
}

void	join_thr(t_philo_data *philo)
{
	int	i;

	i = 0;
	while (i < philo->num_of_philo)
	{
		pthread_join(philo->philos[i].thread, NULL);
		i++;
	}
}
void check_philo(t_philo_data *philo)
{
	while(1)
	{
		pthread_mutex_lock(&philo->d_lock);
		if(philo->someone_died==1)
		{
			free_full(philo);
			pthread_mutex_unlock(&philo->d_lock);
			exit(0);
		}
		pthread_mutex_unlock(&philo->d_lock);
	}
}
void	*sone_died(t_philo_data *philo)
{
	int	i;

	while (42)
	{
		i = 0;
		while (i < philo->num_of_philo)
		{
			pthread_mutex_lock(&philo->d_lock);
			if ((get_time()
					- philo->philos[i].last_meal_time) >= philo->time_to_die)
			{
				printf("%lld %d died\n", get_time() - philo->start_time, i + 1);
				philo->someone_died = 1;
				pthread_mutex_unlock(&philo->d_lock);
				//free_full(philo);
				return (NULL);
			}
			pthread_mutex_unlock(&philo->d_lock);
			i++;
		}
	}
	return (NULL);
}

void	must_eat(t_philo_data *philo)
{
	int	i;
	int c = 0;
	i = 0;
	while(42)
	{
		while (i < philo->num_of_philo)
		{
			pthread_mutex_lock(&philo->must_eat);
			if (philo->philos[i].meals_eaten >= philo->must_eat_c)
				c++;
			pthread_mutex_unlock(&philo->must_eat);
			i++;
		}
		if(c == philo->num_of_philo)
		{
			philo->someone_died=1;
			return ;
		}
	}
	free_full(philo);
	exit(0);
}

int	check_arg(int argc, char *argv[])
{
	int i = 1;
	int j = 0;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
			{
				printf("arg is not numeric!\n");
				return 0;
			}
			j++;
		}
		i++;
	}
	return 1;
}