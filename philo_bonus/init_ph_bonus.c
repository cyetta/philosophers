/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ph_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 14:41:14 by cyetta            #+#    #+#             */
/*   Updated: 2022/05/28 17:19:30 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>
#include "philo_bonus.h"
#include "ft_util_bonus.h"
#include "ft_error_bonus.h"

int	init_ph(t_ph_param *params, t_philo *philo)
{
	params->a_philo = (pid_t *)malloc(sizeof(pid_t) * params->numb_philo);
	if (!params->a_philo)
		return (ERR_INIT_PH_ARR);
	memset(params->a_philo, 0, sizeof(pid_t) * params->numb_philo);
	philo->param = params;
	philo->ph_num = 0;
	philo->eat_cnt = 0;
	return (0);
}

int	clean_ph(t_ph_param *params)
{
	int		i;
	pid_t	child_pid;
	int		status;

	i = -1;
	while (++i < params->numb_philo)
	{
		sem_wait(params->sm_aph_accss);
		if (params->a_philo[i] > 0)
			kill(params->a_philo[i], SIGTERM);
		sem_post(params->sm_aph_accss);
	}
	if (params->ate_monitor)
		kill(params->ate_monitor, SIGTERM);
	child_pid = waitpid(-1, &status, 0);
	while (child_pid != -1)
			child_pid = waitpid(-1, &status, 0);
	if (errno != ECHILD)
		exit(ft_error(ERR_WAITPID));
	close_semph(params);
	free(params->a_philo);
	return (0);
}

int	ph_error(t_philo *philo)
{
	clean_ph(philo->param);
	return (ERR_INIT_PH_ARR);
}

int	lunch_ph(t_philo *philo)
{
	int	i;

	gettimeofday(&philo->param->time_start, NULL);
	i = -1;
	while (++i < philo->param->numb_philo)
	{
		philo->ph_num = i + 1;
		philo->sm_lsteat = philo->param->a_sm_lasteat[i];
		philo->param->a_philo[i] = fork();
		if (philo->param->a_philo[i] < 0)
			return (ph_error(philo));
		else if (philo->param->a_philo[i] == 0)
			phil_start(philo);
	}
	philo->param->ate_monitor = fork();
	if (philo->param->ate_monitor < 0)
		return (ph_error(philo));
	else if (philo->param->ate_monitor == 0)
		ate_monitor(philo->param);
	return (0);
}
