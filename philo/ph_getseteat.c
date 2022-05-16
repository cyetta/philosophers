/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_getseteat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 01:54:04 by cyetta            #+#    #+#             */
/*   Updated: 2022/05/17 00:34:49 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_ph_eatcnt(t_philo *ph, int eat_cnt)
{
	pthread_mutex_lock(ph->mtx_eatcnt);
	ph->eat_cnt = eat_cnt;
	pthread_mutex_unlock(ph->mtx_eatcnt);
}

int	get_ph_eatcnt(t_philo *ph)
{
	int	ret;

	pthread_mutex_lock(ph->mtx_eatcnt);
	ret = ph->eat_cnt;
	pthread_mutex_unlock(ph->mtx_eatcnt);
	return (ret);
}

void	set_ph_lasteat(t_philo *ph)
{
	pthread_mutex_lock(ph->mtx_lasteat);
	gettimeofday(&ph->last_eat, NULL);
	pthread_mutex_unlock(ph->mtx_lasteat);
}

t_timeval	get_ph_lasteat(t_philo *ph)
{
	t_timeval	ret;

	pthread_mutex_lock(ph->mtx_lasteat);
	ret = ph->last_eat;
	pthread_mutex_unlock(ph->mtx_lasteat);
	return (ret);
}
