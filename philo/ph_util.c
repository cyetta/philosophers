/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_util.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 16:29:22 by cyetta            #+#    #+#             */
/*   Updated: 2022/04/15 15:31:19 by cyetta           ###   ########.fr       */
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

void	ph_msg(t_philo *ph, char *msg)
{
	pthread_mutex_lock(&ph->param->mtx_print);
	if (!ph->param->end_smltn && ph->is_live)
		printf("%ld %d %s", ft_timestamp(ph->param->start), ph->ph_num, msg);
	pthread_mutex_unlock(&ph->param->mtx_print);
}

	// pthread_mutex_lock(ph->mtx_rforks);
	// ph_msg(ph, "take a lfork\n");
	// pthread_mutex_lock(ph->mtx_lforks);
	// ph_msg(ph, "take a rfork\n");
void	take_a_fork(t_philo *ph)
{
	if (ph->ph_num == ph->param->numb_philo)
	{
		pthread_mutex_lock(ph->mtx_rforks);
		ph_msg(ph, "take a rfork\n");
		pthread_mutex_lock(ph->mtx_lforks);
		ph_msg(ph, "take a lfork\n");
	}
	else
	{
		pthread_mutex_lock(ph->mtx_lforks);
		ph_msg(ph, "take a lfork\n");
		pthread_mutex_lock(ph->mtx_rforks);
		ph_msg(ph, "take a rfork\n");
	}
}

void	put_a_fork(t_philo *ph)
{
	pthread_mutex_unlock(ph->mtx_rforks);
	ph_msg(ph, "put a rfork\n");
	pthread_mutex_unlock(ph->mtx_lforks);
	ph_msg(ph, "put a lfork\n");
}
	// if (ph->ph_num == 1)
	// {
	// 	pthread_mutex_unlock(ph->mtx_rforks);
	// 	ph_msg(ph, "put a lfork\n");
	// 	pthread_mutex_unlock(ph->mtx_lforks);
	// 	ph_msg(ph, "put a rfork\n");
	// }
	// else
	// {
	// 	pthread_mutex_lock(ph->mtx_lforks);
	// 	ph_msg(ph, "take a rfork\n");
	// 	pthread_mutex_lock(ph->mtx_rforks);
	// 	ph_msg(ph, "take a lfork\n");
	// }

/*
Print philosoph die.
set end_simulation flag and reset is_live thread flag
*/
void	*ph_msg_died(t_philo *ph)
{
	pthread_mutex_lock(&ph->param->mtx_print);
	ph->param->end_smltn = 1;
	ph->is_live = 0;
	printf("%ld %d is died\n", ft_timestamp(ph->param->start), ph->ph_num);
	pthread_mutex_unlock(&ph->param->mtx_print);
	return (NULL);
}
