/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_msg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:58:45 by cyetta            #+#    #+#             */
/*   Updated: 2022/05/17 00:44:46 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_error.h"
#include "ft_util.h"
#include "philo.h"

/*
Prints message from philosoph while them not dead
*/
int	ph_msg(t_philo *ph, char *msg)
{
	pthread_mutex_lock(&ph->param->mtx_print);
	if (get_ph_stat(ph) != PH_ISLIVE)
	{
		pthread_mutex_unlock(&ph->param->mtx_print);
		return (1);
	}
	printf("%ld %d %s", ft_timestamp(ph->param->time_start), ph->ph_num, msg);
	pthread_mutex_unlock(&ph->param->mtx_print);
	return (0);
}

/*
Print philosoph die. Set end_simulation flag
put the forks
*/
int	ph_msg_died(t_ph_param *params, t_philo *ph_arr, int i)
{
	pthread_mutex_lock(&params->mtx_print);
	printf("%ld %d is died\n", ft_timestamp(params->time_start), \
	ph_arr[i].ph_num);
	end_simulation(params, ph_arr);
	put_a_fork(&ph_arr[i]);
	pthread_mutex_unlock(&params->mtx_print);
	return (0);
}
