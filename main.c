/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buket <buket@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:30:27 by bucolak           #+#    #+#             */
/*   Updated: 2025/03/07 00:02:04 by buket            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mutex_init(t_philo_data *philo)
{
	int	i;

	i = 0;
	while (i < philo->num_of_philo)
	{
		pthread_mutex_init(&philo->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&philo->meal_lock, NULL);
	pthread_mutex_init(&philo->m_lock, NULL);
	pthread_mutex_init(&philo->t_lock, NULL);
	pthread_mutex_init(&philo->must_eat, NULL);
	pthread_mutex_init(&philo->d_lock, NULL);
	pthread_mutex_init(&philo->d2_lock, NULL);
	pthread_mutex_init(&philo->d3_lock, NULL);
	pthread_mutex_init(&philo->d4_lock, NULL);
}

int	main(int argc, char *argv[])
{
	t_philo_data	*philo;

	if (argc > 6 || argc < 5)
	{
		printf("There is no enough arguments!\n");
		return (0);
	}
	check_arg(argc, argv);
	philo = malloc(sizeof(t_philo_data));
	philo->forks = NULL;
	philo->philos = NULL;
	philo->start_time = get_time();
	philo->someone_died = 0;
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	philo->num_of_philo = ft_atoi(argv[1]);
	philo->forks = malloc(sizeof(pthread_mutex_t) * philo->num_of_philo);
	philo->philos = malloc(sizeof(t_philo) * philo->num_of_philo);
	philo->fork=malloc(sizeof(t_fork));
	mutex_init(philo);
	create_philo(philo);
	if (argc == 6)
	{
		philo->must_eat_c = ft_atoi(argv[5]);
		must_eat(philo);
	}
	sone_died(philo);
	join_thr(philo);
	free_full(philo);
	return (0);
}
