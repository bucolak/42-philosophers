/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buket <buket@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:51:16 by bucolak           #+#    #+#             */
/*   Updated: 2025/03/07 00:16:50 by buket            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int					is_eating;
	int					is_sleeping;
	int					id;
	int					meals_eaten;
	int					left_fork;
	int					right_fork;
	long long			last_meal_time;
	int aa;
	struct s_philo_data	*data;
	pthread_t			thread;
}						t_philo;

typedef struct s_philo_data
{
	int					num_of_philo;
	t_philo				*philos;
	int					time_to_eat;
	int					time_to_die;
	int					time_to_sleep;
	int					must_eat_c;
	int					someone_died;
	int					two;
	long long			start_time;
	pthread_mutex_t		*forks;
	struct s_fork *fork;
	pthread_mutex_t		meal_lock;
	pthread_mutex_t		m_lock;
	pthread_mutex_t		t_lock;
	pthread_mutex_t		must_eat;
	pthread_mutex_t		d_lock;
	pthread_mutex_t		d2_lock;
	pthread_mutex_t		d3_lock;
	pthread_mutex_t		d4_lock;
}						t_philo_data;

typedef struct s_fork
{
	int b;
	int id;
}	t_fork;

long long				get_time(void);
void					create_philo(t_philo_data *philo);
int						ft_atoi(const char *str);
void					*sone_died(t_philo_data *philo);
void					*philo_routine_2(void *arg);
void					join_thr(t_philo_data *philo);
void					free_full(t_philo_data *philo);
void						must_eat(t_philo_data *philo);
void					check_arg(int argc, char *argv[]);

#endif