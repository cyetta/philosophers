/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 17:39:59 by cyetta            #+#    #+#             */
/*   Updated: 2022/05/28 17:30:30 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>
#include "philo_bonus.h"
#include "ft_util_bonus.h"
#include "ft_error_bonus.h"

int	load_parameters(t_ph_param *params, int argc, char **argv)
{
	memset(params, 0, sizeof(t_ph_param));
	if (ft_atoi_ovfl(argv[1], &params->numb_philo) || \
	ft_atoi_ovfl(argv[2], &params->time_to_die) || \
	ft_atoi_ovfl(argv[3], &params->time_to_eat) || \
	ft_atoi_ovfl(argv[4], &params->time_to_sleep))
		return (1);
	if (params->numb_philo < 1 || params->time_to_die < 1 || \
	params->time_to_eat < 1 || params->time_to_sleep < 1)
		return (1);
	if (argc == 6 && ft_atoi_ovfl(argv[5], &params->numb_ph_eat))
		return (1);
	if (argc == 6 && params->numb_ph_eat < 0)
		return (1);
	if (argc == 5)
		params->numb_ph_eat = 0;
	return (0);
}

int	ate_monitor(t_ph_param	*params)
{
	int			i;

	if (!params->numb_ph_eat)
		exit (0);
	i = -1;
	while (++i < params->numb_philo)
		sem_wait(params->sm_eatcnt);
	i = -1;
	while (++i < params->numb_philo)
	{
		sem_wait(params->sm_aph_accss);
		if (params->a_philo[i] > 0)
			kill(params->a_philo[i], SIGTERM);
		sem_post(params->sm_aph_accss);
	}
	exit (0);
}

int	foget_child(t_ph_param *params, pid_t child_pid)
{
	int	i;

	i = -1;
	while (++i < params->numb_philo)
		if (params->a_philo[i] == child_pid)
			break ;
	if (i == params->numb_philo)
		return (0);
	sem_wait(params->sm_aph_accss);
	params->a_philo[i] = 0;
	sem_post(params->sm_aph_accss);
	return (0);
}

int	wait_simulation(t_ph_param *params)
{
	int			status;
	pid_t		child_pid;

	child_pid = waitpid(-1, &status, 0);
	while (child_pid != -1)
	{
		if (foget_child(params, child_pid))
			exit(ft_error(ERR_UNKNOWN));
		if (status >> 8 == PHILO_DIE)
			return (PHILO_DIE);
		child_pid = waitpid(-1, &status, 0);
	}
	if (errno != ECHILD)
		exit(ft_error(ERR_WAITPID));
	return (0);
}

int	main(int argc, char **argv)
{
	t_ph_param	params;
	t_philo		philo;

	if (argc != 5 && argc != 6)
		return (ft_error(ERR_ARGUMENT));
	else if (load_parameters(&params, argc, argv))
		return (ft_error(ERR_ARGUMENT));
	else if (init_semph(&params))
	{
		close_semph(&params);
		return (ft_error(ERR_SEMAPHOREINIT));
	}
	if (init_ph(&params, &philo))
		return (ft_error(ERR_INIT_PH_ARR));
	if (lunch_ph(&philo))
		return (ft_error(ERR_INIT_PH_ARR));
	wait_simulation(&params);
	clean_ph(&params);
	return (0);
}
