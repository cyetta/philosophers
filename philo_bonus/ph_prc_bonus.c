/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_prc_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 18:58:12 by cyetta            #+#    #+#             */
/*   Updated: 2022/05/24 20:28:27 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "philo_bonus.h"
#include "ft_util.h"

void	*monitor(void *mon)
{
	t_philo	*ph;

	ph = (t_philo *)mon;
	while (1)
	{
		if (ft_timestamp(ph->last_eat) > ph->param->time_to_die)
			exit(ph_msg_died(ph));
		if (ph->param->numb_ph_eat > 0 && ph->eat_cnt >= ph->param->numb_ph_eat)
			exit(PHILO_ATE);
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
	gettimeofday(&philo->last_eat, NULL);
	pthread_create(&mon, NULL, monitor, philo);
	pthread_detach(mon);
	i = -1;
	while (1)
	{
		getafork(philo);
		ph_msg(philo, "is eating\n");
		ft_msleep(philo->param->time_to_eat);
		putafork(philo);
		gettimeofday(&philo->last_eat, NULL);
		philo->eat_cnt++;
		ph_msg(philo, "is sleeping\n");
		ft_msleep(philo->param->time_to_sleep);
		ph_msg(philo, "is thinking\n");
	}
	exit(0);
}
