/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 01:46:57 by cyetta            #+#    #+#             */
/*   Updated: 2022/04/10 17:57:07 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include "ft_error.h"
#include "philo.h"

int	clear_ph(t_ph_param *params, t_philo *ph_arr)
{
	int	i;

	i = -1;
	while (++i < params->numb_philo)
		pthread_mutex_destroy(&params->mtx_forks[i]);
	pthread_mutex_destroy(&params->mtx_print);
	free(ph_arr);
	free(params->mtx_forks);
	return (0);
}

int	create_mutex(t_ph_param *params)
{
	int	i;

	i = -1;
	while (++i < params->numb_philo)
		if (pthread_mutex_init(&params->mtx_forks[i], NULL))
			break ;
	if (i != params->numb_philo)
	{
		while (--i >= 0)
			pthread_mutex_destroy(&params->mtx_forks[i]);
		return (ERR_INIT_PH_ARR);
	}
	if (pthread_mutex_init(&params->mtx_print, NULL))
	{
		i = -1;
		while (++i < params->numb_philo)
			pthread_mutex_destroy(&params->mtx_forks[i]);
		return (ERR_INIT_PH_ARR);
	}
	return (0);
}

int	create_pharr(t_ph_param *params, t_philo **ph_arr)
{
	*ph_arr = (t_philo *) malloc(sizeof(t_philo) * params->numb_philo);
	if (!*ph_arr)
		return (ERR_INIT_PH_ARR);
	params->mtx_forks = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t) \
	* params->numb_philo);
	if (!params->mtx_forks)
	{
		free(*ph_arr);
		return (ERR_INIT_PH_ARR);
	}
	if (create_mutex(params))
	{
		free(*ph_arr);
		free(params->mtx_forks);
		return (ERR_INIT_PH_ARR);
	}
	return (0);
}

int	init_ph(t_ph_param *params, t_philo **ph_arr)
{
	int	i;

	if (create_pharr(params, ph_arr))
		return (ERR_INIT_PH_ARR);
	i = -1;
	gettimeofday(&params->start, NULL);
	while (++i < params->numb_philo)
	{
		(*ph_arr)[i].ph_num = i + 1;
		(*ph_arr)[i].param = params;
		(*ph_arr)[i].mtx_lforks = &params->mtx_forks[i];
		(*ph_arr)[i].mtx_rforks = &params->mtx_forks[(i + 1) \
		% params->numb_philo];
		(*ph_arr)[i].is_die = 0;
		gettimeofday(&((*ph_arr)[i].last_eat), NULL);
		pthread_create(&((*ph_arr)[i].ph_thread), NULL, \
		philosoph, &(*ph_arr)[i]);
	}
	return (0);
}
