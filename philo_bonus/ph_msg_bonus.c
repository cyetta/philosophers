/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_msg_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:04:17 by cyetta            #+#    #+#             */
/*   Updated: 2022/05/28 17:20:21 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "philo_bonus.h"
#include "ft_util_bonus.h"
#include "ft_error_bonus.h"

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

/*
Print philosoph die.
*/
int	ph_msg_died(t_philo *ph)
{
	sem_wait(ph->param->sm_print);
	printf("%ld %d is died\n", ft_timestamp(ph->param->time_start), ph->ph_num);
	return (PHILO_DIE);
}
