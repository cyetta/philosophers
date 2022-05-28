/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_getset_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 16:28:06 by cyetta            #+#    #+#             */
/*   Updated: 2022/05/28 17:13:10 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_timeval	get_lasteat(t_philo *philo)
{
	t_timeval	ret;

	sem_wait(philo->sm_lsteat);
	ret = philo->last_eat;
	sem_post(philo->sm_lsteat);
	return (ret);
}

void	set_lasteat(t_philo *philo)
{
	sem_wait(philo->sm_lsteat);
	gettimeofday(&philo->last_eat, NULL);
	sem_post(philo->sm_lsteat);
}
