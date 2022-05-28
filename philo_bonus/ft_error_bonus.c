/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 18:06:26 by cyetta            #+#    #+#             */
/*   Updated: 2022/05/28 17:16:16 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_error_bonus.h"

static int	usage(void)
{
	printf("Usage: ./philo number_of_philosophers time_to_die time_to_eat \
time_to_sleep [number_of_times_each_philosopher_must_eat] \n◦ \
number_of_philosophers: The number of philosophers and also the number of \
forks.\n◦ time_to_die (in milliseconds): If a philosopher didn’t start \
eating time_to_die milliseconds since the beginning of their last meal or \
the beginning of the simulation, they die.\n◦ time_to_eat (in milliseconds): \
The time it takes for a philosopher to eat. During that time, they will need \
to hold two forks.\n◦ time_to_sleep (in milliseconds): The time a philosopher \
will spend sleeping.\n◦ number_of_times_each_philosopher_must_eat (optional \
argument): If all philosophers have eaten at least \
number_of_times_each_philosopher_must_eat times, the simulation stops. If not \
specified, the simulation stops when a philosopher dies.\n");
	return (1);
}

int	err_msg(char *msg, int err)
{
	printf("%s %d\n", msg, err);
	return (err);
}

int	ft_error(int errnum)
{
	if (errnum == ERR_ARGUMENT)
		return (usage());
	else if (errnum == ERR_ATOI_NOTVALUE)
		return (err_msg("Not value. Error ", errnum));
	else if (errnum == ERR_ATOI_OVER)
		return (err_msg("Value overflow. Error ", errnum));
	else if (errnum == ERR_INIT_PH_ARR)
		return (err_msg("Array of philosopher not created. Error ", errnum));
	else if (errnum == ERR_INIT_PTH_ARR)
		return (err_msg("Philosopher thread not created. Error ", errnum));
	else if (errnum == ERR_WAITPID)
		return (err_msg("Wait child process error. Error ", errnum));
	else if (errnum == ERR_SEMAPHOREINIT)
		return (err_msg("Semaphore create error. Error ", errnum));
	else
		return (err_msg("Unknown error ", errnum));
}
