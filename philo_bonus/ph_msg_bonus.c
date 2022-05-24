/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_msg_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:04:17 by cyetta            #+#    #+#             */
/*   Updated: 2022/05/24 18:17:06 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_error.h"
#include "ft_util.h"
#include "philo_bonus.h"

/*
Prints message from philosoph while them not dead
*/
int	ph_msg(t_philo *ph, char *msg)
{
	sem_wait(ph->param->sm_print);
	printf("%ld %d %s", ft_timestamp(ph->param->time_start), ph->ph_num, msg);
	sem_post(ph->param->sm_print);
	return (0);
}

	// if (get_ph_stat(ph) != PH_ISLIVE)
	// {
	// 	pthread_mutex_unlock(&ph->param->mtx_print);
	// 	return (1);
	// }
/*
Print philosoph die. Set end_simulation flag
put the forks
*/
int	ph_msg_died(t_philo *ph)
{
	sem_wait(ph->param->sm_print);
	printf("%ld %d is died\n", ft_timestamp(ph->param->time_start), ph->ph_num);
	return (PHILO_DIE);
}
