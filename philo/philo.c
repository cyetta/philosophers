/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 17:39:59 by cyetta            #+#    #+#             */
/*   Updated: 2022/04/02 20:45:44 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include "ft_error.h"
#include "ft_util.h"
#include "philo.h"

int	load_parameters(t_philo *params, int argc, char **argv)
{
	memset(params, 0, sizeof(t_philo));
	if (ft_atoi_ovfl(argv[1], &params->numb_philo) || \
	ft_atoi_ovfl(argv[2], &params->time_to_die) || \
	ft_atoi_ovfl(argv[3], &params->time_to_eat) || \
	ft_atoi_ovfl(argv[4], &params->time_to_sleep))
		return (1);
	if (argc == 6 && ft_atoi_ovfl(argv[5], &params->numb_ph_eat))
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo	params;

	if (argc != 5 && argc != 6)
		return (ft_error(ERR_ARGUMENT));
	if (load_parameters(&params, argc, argv))
		return (ft_error(ERR_ARGUMENT));
	printf("Number_of_philosophers %d\ntime_to_die %d\ntime_to_eat %d\n\
time_to_sleep %d\n[number_of_times_each_philosopher_must_eat] %d\n", \
params.numb_philo, params.time_to_die, params.time_to_eat, \
params.time_to_sleep, params.numb_ph_eat);
}
