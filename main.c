/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bucolak <bucolak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:30:27 by bucolak           #+#    #+#             */
/*   Updated: 2025/03/21 16:32:04 by bucolak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	variable_of_two_cont(t_philo_data *philo, int i)
{
	if (philo->two != 1)
		printf("%lld %d died\n", get_time() - philo->start_time, i
			+ 1);
}

void	mutex_init(t_philo_data *philo)
{
	int	i;

	i = 0;
	while (i < philo->num_of_philo)
	{
		pthread_mutex_init(&philo->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&philo->d_lock, NULL);
}

void	st_init(t_philo_data *philo, char *argv[])
{
	int	i;

	i = 0;
	philo->forks = NULL;
	philo->philos = NULL;
	philo->start_time = get_time();
	philo->someone_died = 0;
	philo->two = 0;
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	philo->num_of_philo = ft_atoi(argv[1]);
	philo->forks = malloc(sizeof(pthread_mutex_t) * philo->num_of_philo);
	philo->philos = malloc(sizeof(t_philo) * philo->num_of_philo);
	while (i < philo->num_of_philo)
	{
		philo->philos[i].id = i + 1;
		philo->philos[i].last_meal_time = philo->start_time;
		philo->philos[i].meals_eaten = 0;
		philo->philos[i].data = philo;
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_philo_data	*philo;

	if (argc > 6 || argc < 5)
	{
		printf("There is no enough arguments!\n");
		return (0);
	}
	philo = malloc(sizeof(t_philo_data));
	philo->argc = argc;
	philo->must_eat_c = 0;
	if (argc == 6)
		philo->must_eat_c = ft_atoi(argv[5]);
	st_init(philo, argv);
	mutex_init(philo);
	if (check_arg(argc, argv) == 1)
	{
		create_philo(philo);
		free_full(philo);
		return (0);
	}
	free_full(philo);
	return (0);
}
