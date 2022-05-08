/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 01:46:57 by cyetta            #+#    #+#             */
/*   Updated: 2022/05/08 20:20:27 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <string.h>
#include "ft_error.h"
#include "philo.h"

	// int	ph_live;
	// ph_live = 1;
	// while (ph_live)
	// {
	// 	ph_live = 0;
	// 	i = -1;
	// 	while (++i < params->numb_philo)
	// 		ph_live += ph_arr[i].is_live;
	// }
int	clear_ph(t_ph_param *params, t_philo *ph_arr)
{
	int	i;

	i = -1;
	while (++i < params->numb_philo)
	{
		printf("join thread %d \n", i);
		pthread_join(ph_arr[i].ph_thread, NULL);
	}
	i = -1;
	printf("thread joined\n");
	while (++i < params->numb_philo)
		pthread_mutex_destroy(&params->mtx_forks[i]);
	pthread_mutex_destroy(&params->mtx_smltn);
	pthread_mutex_destroy(&params->mtx_print);
	free(ph_arr);
	free(params->mtx_forks);
	return (0);
}

int	ph_mtx_init(t_ph_mtx *mtx)
{
	if (pthread_mutex_init(&mtx->mtx_eatcnt, NULL))
		return (ERR_INIT_PTH_ARR);
	else if (pthread_mutex_init(&mtx->mtx_fork, NULL))
	{
		pthread_mutex_destroy(&mtx->mtx_eatcnt);
		return (ERR_INIT_PTH_ARR);
	}
	else if (pthread_mutex_init(&mtx->mtx_islive, NULL))
	{
		pthread_mutex_destroy(&mtx->mtx_eatcnt);
		pthread_mutex_destroy(&mtx->mtx_fork);
		return (ERR_INIT_PTH_ARR);
	}
	return (0);
}

int	ph_mtx_dest(t_ph_mtx *mtx)
{
	pthread_mutex_destroy(&mtx->mtx_eatcnt);
	pthread_mutex_destroy(&mtx->mtx_fork);
	pthread_mutex_destroy(&mtx->mtx_islive);
}

int	create_mutex(t_ph_param *params)
{
	int	i;

	if (pthread_mutex_init(&params->mtx_print, NULL))
		return (ERR_INIT_PH_ARR);
	i = -1;
	while (++i < params->numb_philo)
		if (ph_mtx_init(&params->mtx_arr_forks[i]))
			break ;
	if (i != params->numb_philo)
	{
		while (--i >= 0)
			ph_mtx_dest(&params->mtx_arr_forks[i]);
		pthread_mutex_destroy(&params->mtx_print);
		return (ERR_INIT_PH_ARR);
	}
	return (0);
}

int	create_pharr(t_ph_param *params, t_philo **ph_arr)
{
	*ph_arr = (t_philo *) malloc(sizeof(t_philo) * params->numb_philo);
	if (!*ph_arr)
		return (ERR_INIT_PH_ARR);
	memset((void *)*ph_arr, 0, sizeof(t_philo) * params->numb_philo);
	params->mtx_arr_forks = (t_ph_mtx *) malloc(sizeof(t_ph_mtx) \
	* params->numb_philo);
	if (!params->mtx_arr_forks)
	{
		free(*ph_arr);
		return (ERR_INIT_PH_ARR);
	}
	if (create_mutex(params))
	{
		free(*ph_arr);
		free(params->mtx_arr_forks);
		return (ERR_INIT_PH_ARR);
	}
	return (0);
}

int	lunch_ph(t_ph_param *params, t_philo *philo, int ph_num)
{
	philo->ph_num = ph_num + 1;
	philo->param = params;
	philo->mtx_lforks = &params->mtx_arr_forks[ph_num].mtx_fork;
	philo->mtx_rforks = &params->mtx_arr_forks[(ph_num + 1) % \
	params->numb_philo].mtx_fork;
	gettimeofday(&philo->last_eat, NULL);
	if (pthread_create(&philo->ph_thread, NULL, philosoph, philo))
		return (ERR_INIT_PTH_ARR);
	return (0);
}

int	init_ph(t_ph_param *params, t_philo **ph_arr)
{
	int	i;

	if (create_pharr(params, ph_arr))
		return (ERR_INIT_PH_ARR);
	i = -1;
	gettimeofday(&params->time_start, NULL);
	while (++i < params->numb_philo)
		if (lunch_ph(params, &(*ph_arr)[i], i))
			break;
	if (i == params->numb_philo)
		return (0);
	clear_ph(params, *ph_arr);
	return (ERR_INIT_PH_ARR);
}
		// (*ph_arr)[i].is_live = 1;
