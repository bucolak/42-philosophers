/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bucolak <bucolak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 18:08:15 by bucolak           #+#    #+#             */
/*   Updated: 2025/02/20 18:11:14 by bucolak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long long get_time_bonus()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return(tv.tv_sec*1000 + tv.tv_usec/1000);
}