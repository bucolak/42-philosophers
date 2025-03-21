/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bucolak <bucolak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:51:16 by bucolak           #+#    #+#             */
/*   Updated: 2025/03/21 16:32:19 by bucolak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int					id;
	int					meals_eaten;
	long long			last_meal_time;
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
	int					argc;
	long long			start_time;
	pthread_mutex_t		*forks;
	pthread_mutex_t		d_lock;

}						t_philo_data;

long long				get_time(void);
void					create_philo(t_philo_data *philo);
int						ft_atoi(const char *str);
void					*sone_died(void *arg);
void					*philo_routine(void *arg);
void					join_thr(t_philo_data *philo);
void					free_full(t_philo_data *philo);
int						check_arg(int argc, char *argv[]);
void					check_philo(t_philo_data *philo);
int						ft_usleep(size_t milliseconds);
int						cont_dead(t_philo *philo);
int						must_eaten(t_philo_data *philo);
void					dead_cont_2(t_philo *philo, int left_id, int right_id);
void					variable_of_two_cont(t_philo_data *philo, int i);

#endif