/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_getsetstat.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 01:54:04 by cyetta            #+#    #+#             */
/*   Updated: 2022/05/17 00:34:49 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_ph_stat(t_philo *ph, t_phstatus stat)
{
	pthread_mutex_lock(ph->mtx_islive);
	ph->is_live = stat;
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
