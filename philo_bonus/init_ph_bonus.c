/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ph_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 14:41:14 by cyetta            #+#    #+#             */
/*   Updated: 2022/05/25 16:25:35 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>
#include "philo_bonus.h"
#include "ft_util.h"
#include "ft_error.h"

int	init_ph(t_ph_param *params, t_philo *philo, pid_t **a_philo)
{
	*a_philo = (pid_t *)malloc(sizeof(pid_t) * params->numb_philo);
	if (!*a_philo)
		return (ERR_INIT_PH_ARR);
	memset(*a_philo, 0, sizeof(pid_t) * params->numb_philo);
	philo->param = params;
	philo->ph_num = 0;
	philo->eat_cnt = 0;
	return (0);
}

int	clean_ph(t_ph_param *params, pid_t *a_philo)
{
	int		i;
	pid_t	child_pid;
	int		status;

	i = -1;
	while (++i < params->numb_philo)
	{
		if (a_philo[i] > 0)
		{
			printf("%5dkill pid %d\n", i, a_philo[i]);
			kill(a_philo[i], SIGTERM);
		}
	}
	child_pid = waitpid(-1, &status, 0);
	while (child_pid != -1)
			child_pid = waitpid(-1, &status, 0);
	if (errno != ECHILD)
		exit(ft_error(ERR_WAITPID));
	close_semph(params);
	free(a_philo);
	return (0);
}

int	lunch_pherr(t_philo *philo, pid_t *a_philo)
{
	clean_ph(philo->param, a_philo);
	return (ERR_INIT_PH_ARR);
}

int	lunch_ph(t_philo *philo, pid_t *a_philo)
{
	int	i;

	gettimeofday(&philo->param->time_start, NULL);
	i = -1;
	while (++i < philo->param->numb_philo)
	{
		philo->ph_num = i + 1;
		philo->sm_eatcnt = philo->param->a_ph_smph[i].sm_eatcnt;
		philo->sm_lsteat = philo->param->a_ph_smph[i].sm_lasteat;
		a_philo[i] = fork();
		if (a_philo[i] < 0)
			return (lunch_pherr(philo, a_philo));
		else if (a_philo[i] == 0)
			phil_start(philo);
	}
	return (0);
}
