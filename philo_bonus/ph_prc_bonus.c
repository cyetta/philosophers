/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_prc_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 18:58:12 by cyetta            #+#    #+#             */
/*   Updated: 2022/05/28 17:21:11 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "philo_bonus.h"
#include "ft_util_bonus.h"

void	*monitor(void *mon)
{
	t_philo	*ph;

	ph = (t_philo *)mon;
	while (1)
	{
		if (ft_timestamp(get_lasteat(ph)) > ph->param->time_to_die)
			exit(ph_msg_died(ph));
		usleep(500);
	}
}

int	getafork(t_philo *philo)
{
	sem_wait(philo->param->sm_forks);
	ph_msg(philo, "has taken a fork\n");
	sem_wait(philo->param->sm_forks);
	ph_msg(philo, "has taken a fork\n");
	return (0);
}

int	putafork(t_philo *philo)
{
	sem_post(philo->param->sm_forks);
	sem_post(philo->param->sm_forks);
	return (0);
}

void	phil_start(t_philo *philo)
{
	int			i;
	pthread_t	mon;

	if (ft_timestamp(philo->param->time_start) <= 50)
		ft_msleep(50 - ft_timestamp(philo->param->time_start));
	set_lasteat(philo);
	pthread_create(&mon, NULL, monitor, philo);
	pthread_detach(mon);
	i = -1;
	while (1)
	{
		getafork(philo);
		ph_msg(philo, "is eating\n");
		ft_msleep(philo->param->time_to_eat);
		putafork(philo);
		set_lasteat(philo);
		if (philo->param->numb_ph_eat > 0 && \
	++philo->eat_cnt == philo->param->numb_ph_eat)
			sem_post(philo->param->sm_eatcnt);
		ph_msg(philo, "is sleeping\n");
		ft_msleep(philo->param->time_to_sleep);
		ph_msg(philo, "is thinking\n");
	}
	exit(0);
}
