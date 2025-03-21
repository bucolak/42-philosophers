/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cont_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bucolak <bucolak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:50:43 by bucolak           #+#    #+#             */
/*   Updated: 2025/03/21 16:31:33 by bucolak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_philo(t_philo_data *philo)
{
	pthread_t	main;
	int			i;

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
	t_philo_data	*philo;
	int				i;

	philo = (t_philo_data *)arg;
	while (42)
	{
		i = 0;
		while (i < philo->num_of_philo)
		{
			pthread_mutex_lock(&philo->d_lock);
			if ((get_time()
					- philo->philos[i].last_meal_time) >= philo->time_to_die)
			{
				variable_of_two_cont(philo, i);
				philo->someone_died = 1;
				pthread_mutex_unlock(&philo->d_lock);
				return (NULL);
			}
			pthread_mutex_unlock(&philo->d_lock);
			i++;
		}
		if (philo->argc == 6 && must_eaten(philo) == 1)
			break ;
	}
	return (NULL);
}

int	cont_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->d_lock);
	if (philo->data->someone_died == 1)
	{
		pthread_mutex_unlock(&philo->data->d_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->d_lock);
	return (0);
}

int	check_arg(int argc, char *argv[])
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
			{
				printf("arg is not numeric!\n");
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	must_eaten(t_philo_data *philo)
{
	int	c;
	int	i;

	while (1)
	{
		c = 0;
		i = 0;
		while (i < philo->num_of_philo)
		{
			pthread_mutex_lock(&philo->d_lock);
			if (philo->philos[i].meals_eaten >= philo->must_eat_c)
				c++;
			pthread_mutex_unlock(&philo->d_lock);
			i++;
		}
		if (philo->num_of_philo == c)
		{
			pthread_mutex_lock(&philo->d_lock);
			philo->someone_died = 1;
			philo->two = 1;
			pthread_mutex_unlock(&philo->d_lock);
			return (1);
		}
	}
	return (0);
}
