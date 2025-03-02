/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bucolak <bucolak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:30:27 by bucolak           #+#    #+#             */
/*   Updated: 2025/03/02 19:43:31 by bucolak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
void mutex_init(t_philo_data *philo)
{
	int i;
	i = 0;
	while(i < philo->num_of_philo)
	{
		pthread_mutex_init(&philo->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&philo->meal_lock, NULL);
	pthread_mutex_init(&philo->m_lock, NULL);
	pthread_mutex_init(&philo->t_lock, NULL);
}

int	main(int argc, char *argv[])
{
	t_philo_data	*philo;
	if (argc != 5)
		return (0);
	philo = malloc(sizeof(t_philo_data));
	philo->forks=NULL;
	philo->philos = NULL;
	philo->start_time = get_time();
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	philo->num_of_philo = ft_atoi(argv[1]);
	philo->forks = malloc(sizeof(pthread_mutex_t) * philo->num_of_philo);
	philo->philos = malloc(sizeof(t_philo) * philo->num_of_philo);
	mutex_init(philo);
	create_philo(philo);
	sone_died(philo);
	join_thr(philo);
	free_full(philo);
	return (0);
}
