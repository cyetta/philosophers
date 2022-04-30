/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_util.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 16:29:22 by cyetta            #+#    #+#             */
/*   Updated: 2022/04/30 21:24:10 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include "ft_error.h"
#include "ft_util.h"
#include "philo.h"

void	round_timeval2ms(t_timeval *time)
{
	time->tv_usec += 500;
	if (time->tv_usec > 1000000)
	{
		time->tv_sec++;
		time->tv_usec -= 1000000;
	}
	time->tv_usec = (time->tv_usec / 1000) * 1000;
}

void	ph_msg(t_philo *ph, char *msg)
{
	pthread_mutex_lock(&ph->param->mtx_print);
	ph->time_elapsed += ft_timestamp(ph->time_lastmsg);
	gettimeofday(&ph->time_lastmsg, NULL);
	// round_timeval2ms(&ph->time_lastmsg);
	if (!ph->param->end_smltn && ph->is_live)
		printf("%ld %d %s", ph->time_elapsed, ph->ph_num, msg);
	pthread_mutex_unlock(&ph->param->mtx_print);
}

int	take_a_fork(t_philo *ph)
{
	if (ph->ph_num == ph->param->numb_philo)
	{
		pthread_mutex_lock(ph->mtx_rforks);
		if (ph->param->end_smltn || !ph->is_live)
		{
			pthread_mutex_unlock(ph->mtx_rforks);
			return (1);
		}
		ph_msg(ph, "has taken a fork\n");
		pthread_mutex_lock(ph->mtx_lforks);
		ph_msg(ph, "has taken a fork\n");
	}
	else
	{
		pthread_mutex_lock(ph->mtx_lforks);
		if (ph->param->end_smltn || !ph->is_live)
		{
			pthread_mutex_unlock(ph->mtx_lforks);
			return (1);
		}
		ph_msg(ph, "has taken a fork\n");
		pthread_mutex_lock(ph->mtx_rforks);
		ph_msg(ph, "has taken a fork\n");
	}
	return (0);
}

void	put_a_fork(t_philo *ph)
{
	if (ph->ph_num == ph->param->numb_philo)
	{
		pthread_mutex_unlock(ph->mtx_lforks);
		pthread_mutex_unlock(ph->mtx_rforks);
	}
	else
	{
		pthread_mutex_unlock(ph->mtx_rforks);
		pthread_mutex_unlock(ph->mtx_lforks);
	}
}

/*
Print philosoph die.
set end_simulation flag and reset is_live thread flag
*/
void	*ph_msg_died(t_philo *ph)
{
	pthread_mutex_lock(&ph->param->mtx_print);
	ph->param->end_smltn = 1;
	ph->is_live = 0;
	ph->time_elapsed += ft_timestamp(ph->time_lastmsg);
	gettimeofday(&ph->time_lastmsg, NULL);
	printf("%ld %d is died\n", ph->time_elapsed, ph->ph_num);
	pthread_mutex_unlock(&ph->param->mtx_print);
	return (NULL);
}
