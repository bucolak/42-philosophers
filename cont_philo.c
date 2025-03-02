/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cont_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bucolak <bucolak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:50:43 by bucolak           #+#    #+#             */
/*   Updated: 2025/03/02 18:44:39 by bucolak          ###   ########.fr       */
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
		philo->philos[i].last_meal_time = philo->start_time;
		philo->philos[i].meals_eaten = 0;
		philo->philos[i].data = philo;
		philo->t = 0;
		pthread_create(&philo->philos[i].thread, NULL, philo_routine_2,
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

void	*sone_died(void *arg)
{
	t_philo_data	*philo;
	int				i;

	philo = (t_philo_data *)arg;
	while (42)
	{
		i = 0;
		while (i < philo->num_of_philo)
		{
			if ((get_time()
					- philo->philos[i].last_meal_time) >= philo->time_to_die)
			{
				printf("%lld %d died\n", get_time(), i + 1);
				free_full(philo);
				exit(0);
			}
			i++;
		}
	}
	return (NULL);
}
