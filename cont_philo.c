/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cont_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buket <buket@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:50:43 by bucolak           #+#    #+#             */
/*   Updated: 2025/03/14 22:39:19 by buket            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_philo(t_philo_data *philo)
{
	pthread_t main;
	int	i;

	i = 0;
	while (i < philo->num_of_philo)
	{
		pthread_create(&philo->philos[i].thread, NULL, philo_routine,
			&philo->philos[i]);
		i++;
	}
	pthread_create(&main, NULL, sone_died, philo);
	i = 0;
	while (i < philo->num_of_philo)
	{
		pthread_join(philo->philos[i].thread, NULL);
		i++;
	}
	pthread_join(main, NULL);
}

void	*sone_died(void *arg)
{
	t_philo_data *philo = (t_philo_data *)arg;
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
				return NULL;
			}
			pthread_mutex_unlock(&philo->d_lock);
			i++;
		}
	}
	return (NULL);
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