/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 16:29:22 by cyetta            #+#    #+#             */
/*   Updated: 2022/05/17 00:47:25 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_error.h"
#include "ft_util.h"
#include "philo.h"

int	take_a_lfork(t_philo *ph)
{
	if (get_ph_stat(ph) != PH_ISLIVE)
		return (1);
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
	if (get_ph_stat(ph) != PH_ISLIVE)
		return (1);
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
		{
			pthread_mutex_unlock(ph->mtx_rforks);
			return (1);
		}
	}
	else
	{
		if (take_a_lfork(ph))
			return (1);
		else if (take_a_rfork(ph))
		{
			pthread_mutex_unlock(ph->mtx_lforks);
			return (1);
		}
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
