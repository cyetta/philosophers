/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_getset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 01:54:04 by cyetta            #+#    #+#             */
/*   Updated: 2022/05/09 01:58:03 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "philo.h"

void	set_ph_stat(t_philo *ph, t_phstatus stat)
{
	pthread_mutex_lock(ph->mtx_islive);
	ph->is_live = PH_TODIE;
	pthread_mutex_unlock(ph->mtx_islive);
}

t_phstatus	get_ph_stat(t_philo *ph)
{
	t_phstatus	ret;

	pthread_mutex_lock(ph->mtx_islive);
	ret = ph->is_live;
	pthread_mutex_unlock(ph->mtx_islive);
	return (ret);
}

void	set_ph_eatcnt(t_philo *ph, int eat_cnt)
{
	pthread_mutex_lock(ph->mtx_eatcnt);
	ph->eat_cnt = eat_cnt;
	pthread_mutex_unlock(ph->mtx_eatcnt);
}

int	get_ph_eat(t_philo *ph)
{
	int	ret;

	pthread_mutex_lock(ph->mtx_islive);
	ret = ph->eat_cnt;
	pthread_mutex_unlock(ph->mtx_islive);
	return (ret);
}
