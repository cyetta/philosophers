/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_util.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 16:29:22 by cyetta            #+#    #+#             */
/*   Updated: 2022/05/01 20:05:38 by cyetta           ###   ########.fr       */
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

int	ph_msg(t_philo *ph, char *msg)
{
	// if (ph->param->end_smltn || !ph->is_live)
	// 	return (1);
	pthread_mutex_lock(&ph->param->mtx_print);
	if (ph->param->end_smltn || !ph->is_live)
	{
		pthread_mutex_unlock(&ph->param->mtx_print);
		return (1);
	}
	printf("%ld %d %s", ft_timestamp(ph->param->time_start), ph->ph_num, msg);
	pthread_mutex_unlock(&ph->param->mtx_print);
	return (0);
}
	// ph->time_elapsed += ft_timestamp(ph->time_lastmsg);
	// gettimeofday(&ph->time_lastmsg, NULL);
	// round_timeval2ms(&ph->time_lastmsg);

int	take_a_lfork(t_philo *ph)
{
	pthread_mutex_lock(ph->mtx_lforks);
	if (ph_msg(ph, "has taken a fork\n"))
	{
		pthread_mutex_unlock(ph->mtx_lforks);
		return (1);
	}
	return (0);
}

int	take_a_rfork(t_philo *ph)
{
	pthread_mutex_lock(ph->mtx_rforks);
	if (ph_msg(ph, "has taken a fork\n"))
	{
		pthread_mutex_unlock(ph->mtx_rforks);
		return (1);
	}
	return (0);
}

int	take_a_fork(t_philo *ph)
{
	if (ph->ph_num == ph->param->numb_philo)
	{
		if (take_a_rfork(ph))
			return (1);
		else if (take_a_lfork(ph))
			return (1);
	}
	else
	{
		if (take_a_lfork(ph))
			return (1);
		else if (take_a_rfork(ph))
			return (1);
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
void	ph_msg_died(t_philo *ph)
{
	pthread_mutex_lock(&ph->param->mtx_print);
	ph->param->end_smltn = 1;
	ph->is_live = 0;
	printf("%ld %d is died\n", ft_timestamp(ph->param->time_start), ph->ph_num);
	pthread_mutex_unlock(&ph->param->mtx_print);
	put_a_fork(ph);
}
	// printf("msg_died\n");
	// return (NULL);
	// ph->time_elapsed += ft_timestamp(ph->time_lastmsg);
	// gettimeofday(&ph->time_lastmsg, NULL);
